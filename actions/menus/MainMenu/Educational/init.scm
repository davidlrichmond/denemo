(use-modules (ice-9 rdelim))

;; set the random seed up using time of day
(let ((time (gettimeofday)))
  (set! *random-state*
          (seed->random-state (+ (car time)
	                         (cdr time)))))

(define EducationGames::shiftup
  (lambda (n)
    (if (> n 0) (begin
		  (d-CursorUp)
		  (EducationGames::shiftup (- n 1))))))

(define EducationGames::shiftdown
  (lambda (n)
    (if (> n 0) (begin
		  (d-CursorDown)
		  (EducationGames::shiftdown (- n 1))))))

(define (EducationGames::PlaceAnswerStatus gfx)
  (begin
    (d-DirectivePut-note-minpixels "EducationGames::tick" 30)
    (d-DirectivePut-note-gx "EducationGames::tick" -15)
    (d-DirectivePut-note-gy "EducationGames::tick" 40)
    (d-DirectivePut-note-graphic "EducationGames::tick" gfx)))


;;;; Read File ;;;;

(define (EducationGames::ScoreboardFile game_name)
    (string-append (d-LocateDotDenemo) "/" game_name "_scoreboard")
    )

(define EducationGames::ReadScoreboard
 (lambda (scoreboard_file)
  (let ( (load_scoretable 0)
  	 (in_port 0)
	 (scoretable '())
	 (higherscore 0))
  (set! in_port (open-input-file scoreboard_file))

  (set! load_scoretable
    (lambda ()
      (let ( (line "") 
          (uname 0) 
   	  (uscore 0) )
	(set! line (read-line in_port))
      (if  (not (eof-object? line))
        (begin
	  (set! line (string-split line #\:))
	  (set! uname (car line))
	  (set! uscore (string->number (cadr line)))
	  (set! scoretable (acons uname uscore scoretable))
	  (load_scoretable))))))

  (set! higherscore
    (lambda (paira pairb)
      (> (cdr paira) (cdr pairb))))
  (load_scoretable)
  ;sort table
  (set! scoretable (sort scoretable higherscore))
  scoretable
   )))

(define EducationGames::Scoreboard_Pretty_Print
  (lambda (scoreboard_file)
    (let ( (loop 0) 
            (output_string "") )
    (set! loop
      (lambda (score)
        (set! output_string (string-append output_string (string-pad-right (car score) 15 #\space)
    			"\t\t" 
			(number->string (cdr score)) 
			"\n"))
			))
    (map loop (EducationGames::ReadScoreboard scoreboard_file))
    output_string
    )))

;;;; Write File ;;;;
(define EducationGames::Write_Scoreboard_File
  (lambda (scoreboard_file score)
    (let ( (scorefile 0)
  	   (write_user_score 0)
	   (scoretable '())
	   (getusername 0)
	   (TopTen? 0)
	   (OnlyTenInList 0)
	   (AboveLowestScore? 0)
  	  )
    (set! write_user_score 
      (lambda (score)
        (display (car score) scorefile)
        (write-char #\: scorefile)
        (display (cdr score) scorefile)
        (newline scorefile)
        ))
    (set! getusername
      (lambda ()
        (let ( (username "") )
	(set! username 
	  (d-GetUserInput "****Congratulations!!!!****" "Your score has made it to the top 10!!!\nEnter your name here\n" ""))
	username
	)))
    (set! AboveLowestScore?
      (lambda ()
        (let ( (findlowest 0) 
	       (lowest 0) )
	(set! findlowest
	  (lambda (uscore)
	    (if (< (cdr uscore) score)
	       (set! lowest (cdr uscore)))))
	(map findlowest scoretable)
	(> score lowest)
	))) 
    (set! TopTen?
      (lambda ()
        (or 
	  (< (length scoretable) 10)
	  (AboveLowestScore?))
      ))
    (if (file-exists? scoreboard_file)
      (set! scoretable (EducationGames::ReadScoreboard scoreboard_file)))
    (if (TopTen?)
      (begin
        (set! scorefile (open-output-file scoreboard_file))
        (set! scoretable (acons (getusername) score scoretable))
        ;;truncate scoretable
    (set! OnlyTenInList
      (lambda (lst)
        (let ( (list_truncate 0) 
	       (TheList '()) )
	    (set! list_truncate
	      (lambda (n)
		(if (< (length TheList) 10)
		  (set! TheList (append TheList (cons n '())))
		  )))

	    (map list_truncate lst)
	    TheList
	    )))
	(set! scoretable (OnlyTenInList scoretable))
	(map write_user_score scoretable)
        (close-output-port scorefile)#t)#f)

     )))

