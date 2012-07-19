;;;;;;;;;;;;;;; ScoreIndent Set indent
(let ((amount "0.0") (current "0.0")(thematch #f))
  (set! current (d-DirectiveGet-score-prefix "ScoreIndent"))
  (if (boolean? current)
      (set! current "4.0")
      (begin
	(set! thematch (string-match "\\layout \\{indent = ([-0-9.]+)" current))
	;;(display thematch)
	(if (regexp-match? thematch)
	    (set! current (match:substring thematch 1)))))
  (set! amount (d-GetUserInput "Choose indent of first system" "Give amount in decimal" current))
  ;;(display amount)
  (if amount
  	(begin
  		(if (> (string-length amount) 0)
  			(begin
  				(d-DirectivePut-score-prefix "ScoreIndent" (string-append "\\layout {indent = " amount "}\n"))
  				(d-DirectivePut-score-override "ScoreIndent"	DENEMO_OVERRIDE_GRAPHIC)
  				(d-DirectivePut-score-display "ScoreIndent" (string-append "indent=" amount)))
  		(d-DirectiveDelete-score "ScoreIndent"))))
  (d-RefreshDisplay))
