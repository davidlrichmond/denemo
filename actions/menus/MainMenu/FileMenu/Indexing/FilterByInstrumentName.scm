  ;;FilterByInstrumentName
(let ((str "")(search-instrument #f)(tag "IndexEntry")(list-of-entries '()) (thefile #f) (transpose #f) (title #f) (composer #f) (comment #f) (incipit #f) (instruments '())(startdir ""))
    (define (create-lilypond data)
        (if data
            (begin
                (set! thefile (assq-ref data 'thefile))
                (set! transpose (assq-ref data 'transpose))
                (set! title (assq-ref data 'title))
                (set! composer (assq-ref data 'composer))
                (set! comment (assq-ref data 'comment))
                (set! incipit (assq-ref data 'incipit))
                (set! instruments (string-join (assq-ref data 'instruments) ", "))
                (if (string-contains instruments search-instrument)
                   (begin
                      (set! str (string-append str
                        "\\noPageBreak\\markup \"" composer ": " title "\"\n"
                        "\\noPageBreak\\markup {instrumentation:"  instruments "}\n"
                        (if (string-null? comment) "" (string-append "\\noPageBreak\\markup\\bold\\italic {\"Comment:" comment "\"}\n"))
                        transpose "\n"
                        incipit "\n\\noPageBreak\\incipit\n"
                         "\\noPageBreak\\markup {\\with-url #'\"scheme:(d-OpenNewWindow \\\"" thefile "\\\")\" \"Filename: ." (substring thefile (string-prefix-length startdir thefile)) "\"}\n"
                        "\\markup {\\column {\\draw-hline}}")))
              (delq! data DenemoIndexEntries)))))
;;;;actual procedure        
   (let ((data (d-DirectiveGet-movementcontrol-data tag)))
        (if data
           (begin
              (set! startdir (d-DirectiveGet-movementcontrol-data (string-append tag "StartDir")))
              (if (not startdir)
                (set! startdir ""))
              (set! search-instrument (d-GetUserInput (_ "Index Filter") (_ "Give Instrument Name to filter on:") (_ "Violino")))
              (set! DenemoIndexEntries (cons #f (eval-string data))) ;;add an element #f to the start that will match nothing, so delq! does not delete the first element
              (map  create-lilypond (cdr DenemoIndexEntries)) ;start after dummy
              (set! DenemoIndexEntries (cdr DenemoIndexEntries)) ;remove dummy first element
              (d-SetSaved #f)
              (d-DirectivePut-movementcontrol-data tag (format #f "'~s" DenemoIndexEntries))
              (d-DirectivePut-movementcontrol-postfix tag (string-append "\\markup \\bold\\center-column{\\line{Filtered by Instrument "
                      search-instrument 
                      "}}\\markup {\\column {\\draw-hline}} \\markup {\\center-column {\\vspace #2 }}"
                      str
                      "\n\\noPageBreak\\markup {\\column {\\draw-hline}}\\noPageBreak\\markup {\\center-column {\\vspace #2 }}\\noPageBreak\\markup\\huge{" 
                      (_ "End of Index. Number of entries ") (number->string (length DenemoIndexEntries)) ".}")))
            (d-WarningDialog (_ "Create index first")))))
