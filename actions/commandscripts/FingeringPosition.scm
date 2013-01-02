;;; Warning!!! This file is derived from those in actions/menus/... do not edit here
;;;FingeringPosition
(let ((fingering-tag "Fingering"))	
	(define finger #f)
	(define (get-direction text)
		(if text
			text
			"up"))

   ;adds posn as an extra line on display field of note directive
	(define (do-position posn)
		(define finger (d-DirectiveGet-note-display fingering-tag))
		(define (first-line text)
					(if text
						(let ((thelist (string-split text #\newline)))						
								(list-ref thelist 0))
						""))
		(if finger
			(set! finger (first-line finger))
			(set! finger ""))
		(d-DirectivePut-note-display fingering-tag (string-append finger "\n" posn)))
		
		;;;gets the position from the display field of the note
	(define (get-position text)
		(let ((thelist (string-split text #\newline)))
			(if (> (length thelist) 1)
				(list-ref thelist 1)
				"")))
		
	(define (do-up)
				(do-position "up"))
	(define (do-down)
				(do-position "down"))
	(define (do-left)
				(do-position "left"))
	(define (do-right)
				(do-position "right"))
				
	(define (do-finger-positions)
				(define tag "FingeringPositions")
				(define directions "")
				(d-Chordize #t)

				(let loop ((count 1))
						(if	(d-CursorToNote (d-GetNote count))
							(begin
								(set! directions (string-append directions " " (get-direction (get-position (d-DirectiveGet-note-display fingering-tag)))))
								(loop (+ 1 count)))))
				(d-DirectivePut-chord-prefix tag (string-append "\\set fingeringOrientations = #'(" directions ") "))
				(d-DirectivePut-chord-override tag (logior DENEMO_OVERRIDE_DYNAMIC DENEMO_OVERRIDE_AFFIX))
				(d-RefreshDisplay)
				(d-SetSaved #f))		
				
	(define value #f)
			
	(set! value (d-PopupMenu (list (cons (cons (_ "Above") (_ "Places the fingering above the chord")) do-up)
																			(cons (cons (_ "Below") (_ "Places the fingering below the chord")) do-down)
																			(cons (cons (_ "Left") (_ "Places the fingering to the left of the chord")) do-left)
																			(cons (cons (_ "Right") (_ "Places the fingering to the right of the chord")) do-right))))	
	(if value
			(let ((initial (d-GetCursorNoteWithOctave)))
				(value)
				(do-finger-positions)
				(d-CursorToNote initial)
				)))
