;;;NewStaffAfter
(let ((name #f))
	(d-AddAfter)
	(d-InstrumentName)
	(set! name (d-DirectiveGet-staff-display "InstrumentName"))
	(if name	
			(d-StaffProperties (string-append "denemo_name=" name))))