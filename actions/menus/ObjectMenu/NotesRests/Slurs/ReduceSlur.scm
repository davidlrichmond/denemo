;;;ReduceSlur
  (if (d-IsSlurEnd)
    (begin 	
	(d-ToggleEndSlur)
	(if (d-PrevChord)
		(if (d-IsSlurStart)
			(d-ToggleBeginSlur)
			(d-ToggleEndSlur))))
   (begin
   	(if (d-PrevChord)
   		(if (d-IsSlurEnd)
   			(begin 	
				(d-ToggleEndSlur)
				(if (d-PrevChord)
					(if (d-IsSlurStart)
					(d-ToggleBeginSlur)
					(d-ToggleEndSlur))))))))



