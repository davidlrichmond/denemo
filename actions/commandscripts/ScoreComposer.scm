
	(if (d-PreviousMovement)
		(d-WarningDialog "Returning to the first Movement to set this composer"))
	(while (d-PreviousMovement)
		(display "Seeking first movement"))
        (SetHeaderField "composer")
        (DenemoPrintAllHeaders)
        (d-RefreshDisplay)
        