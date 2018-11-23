;;;SortByComposer takes the IndexEntry data sorts them by composer (creates the IndexEntry data from the .DenemoIndex.scm files if it is not already present) and creates and index PDF FIXME take last word of composer not first.
(use-modules (ice-9 ftw))
(let ((str "")(tag "IndexEntry")(list-of-entries '()) (thefile #f) (transpose #f) (title #f) (composer #f) (incipit #f) (instruments '()))
    (define (create-lilypond data)
        (if data
            (begin
                (set! thefile (assq-ref data 'thefile))
                (set! transpose (assq-ref data 'transpose))
                (set! title (assq-ref data 'title))
                (set! composer (assq-ref data 'composer))
                (set! incipit (assq-ref data 'incipit))
                (set! instruments (assq-ref data 'instruments))
                
                (set! str (string-append str
                        "\\markup \"" composer ": " title "\"\n"
                        "\\markup {instrumentation:"  (apply string-append instruments) "}\n"
                        transpose "\n"
                        incipit "\n\\incipit\n"
                        "\\markup {Filename: " thefile "}\n"
                        "\\markup {\\column {\\draw-hline}}")))

            "\\markup { BLANK ENTRY }"))
    (define (comparison a b)
        (define comp1 (assq-ref a 'composer))
        (define comp2 (assq-ref b 'composer))
        (string-ci< comp1 comp2))

    (define (theproc filename statinfo flag) 
       (d-KeepAlive)
       (if (and (eq? flag 'regular) (or (string-suffix? ".DenemoIndex.scm" filename)))
            (let ((port (open-file filename "r")))
                (define data (read port))
                (close-port port)
                (d-SetSaved #f)
                (set! DenemoIndexEntries (cons data DenemoIndexEntries))))
        #t); continue traversal
;;;;actual procedure        
  

  (set! DenemoIndexEntries (d-DirectiveGet-movementcontrol-data tag))
  (if DenemoIndexEntries
    (begin
        (set! DenemoIndexEntries (eval-string DenemoIndexEntries)))
    (let ((startdir #f))
      (define startdir (d-ChooseDirectory "Where to start indexing from" DENEMO_HOME_DIR '()))
      (d-New)
      (d-NonPrintingStaff 'set)
      (d-DirectivePut-standalone-display "Info" (_ "The Index to scores will appear in the Print View"))
      (d-DirectivePut-movementcontrol-postfix tag (string-append "\\markup \\bold \\huge\\center-column{\\line{Index of Music in \\italic {" startdir 
            "}} \\column {\\draw-hline}}\\markup {\\column {\\draw-hline}} \\markup {\\center-column {\\vspace #2 }}   "))
      (set! DenemoIndexEntries '())
      (ftw startdir theproc))) 
  (sort! DenemoIndexEntries comparison)
  (map  create-lilypond DenemoIndexEntries)
  (d-DirectivePut-movementcontrol-postfix tag str)
  (d-DirectivePut-movementcontrol-data tag (format #t "~s" DenemoIndexEntries)))