;;MultiMeasureRests
  (let ((tag #f))
    (define count 0)
    (if (d-Directive-chord? "WholeMeasureRest")
    (begin
      (set! count 1)
      (d-DeleteObject)
      (d-DirectivePut-standalone-minpixels "MultiMeasureRests" 50)
      (d-DirectivePut-standalone-graphic "MultiMeasureRests"  "MultiMeasureRests")
      (d-DirectivePut-standalone-gx  "MultiMeasureRests"  50)
      (d-DirectivePut-standalone-gy "MultiMeasureRests"  -2)
      (d-PushPosition)
      (let loop ()
	(if (d-NextChord)
	    (begin	    
	      (if (d-Directive-chord? "WholeMeasureRest")
		  (begin
		    (set! count (1+ count))
		    (d-DeleteObject)
		    (d-Directive-standalone "WholeMeasureRest")
		    (d-SetDurationInTicks (* 1536 (GetPrevailingTimeSig #t)))
		    (d-DirectivePut-standalone-graphic "WholeMeasureRest" "BracketedWholeMeasureRest")
		    (d-DirectivePut-standalone-gx "WholeMeasureRest" 50)
		    (d-DirectivePut-standalone-gy "WholeMeasureRest" -2)
		    (d-DirectivePut-standalone-postfix "WholeMeasureRest" "%{ grouped rest %}")
		    (d-DirectivePut-standalone-override "WholeMeasureRest" DENEMO_OVERRIDE_LILYPOND)
		    (d-DirectivePut-standalone-display "WholeMeasureRest" "grouped\nas mm rest")
		    (d-DirectivePut-standalone-tx "WholeMeasureRest" 25)
		    (d-DirectivePut-standalone-ty "WholeMeasureRest" -30)
		    (loop))))))
      (d-PopPosition)
      (if (d-Directive-standalone? "MultiMeasureRests")
	  (begin
	    (d-SetDurationInTicks (* 1536 (GetPrevailingTimeSig #t)))
	    (d-DirectivePut-standalone-display "MultiMeasureRests" (string-append "Rest " (number->string count)))
	    (d-DirectivePut-standalone-ty "MultiMeasureRests" -28)  
	    (d-DirectivePut-standalone-postfix "MultiMeasureRests" (string-append "\\set Score.skipBars = ##t R1*" (d-InsertTimeSig "query=timesigname") "*" (number->string count)))
	   ;; (d-DirectivePut-standalone-override "MultiMeasureRests" DENEMO_OVERRIDE_LILYPOND)
	    )))))
    (d-SetSaved #f)	 

