;;RefreshDynamicDirectives
(let loop ((number 0))
  (define tag (d-DirectiveGetNthTag-score number))
  (if tag
    (let ((index (string-index tag #\:)) (command #f) (arg "")) 
    	(if index
    		(begin
		  (set! command (substring tag 0 index))
		  (set! arg (substring tag (+ 1 index))))
    		(set! command tag))
      (set! command (string-append "d-" command))
     ; (disp "looking at " tag "and " command "\n")
      (if (positive? (logand (d-DirectiveGet-score-override tag) DENEMO_OVERRIDE_DYNAMIC))
	(let ((sym (string->symbol command)))
		(if (defined? sym)
	 		 (eval-string (string-append "(" command " \"" arg "\")")))))
      (loop (+ 1 number)))))
;;; FIXME there are 13 other types of directive to refresh ,,,
