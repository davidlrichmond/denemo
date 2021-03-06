;;;;;;;;;;;;
(let ((tag1 "StartBreak")(tag2 "StopBreak"))
    (d-InsertMeasureBefore)
    (d-DirectivePut-standalone tag1)
    (d-DirectivePut-standalone-minpixels tag1 30)
    (d-DirectivePut-standalone-graphic tag1 "\nGAP\nDenemo\n48")
    (d-DirectivePut-standalone-postfix tag1 "\\hideNotes \\stopStaff ")
    (d-WholeMeasureSpacer)
    (d-DirectivePut-standalone tag2)
    (d-DirectivePut-standalone-postfix tag2 (string-append
        "\\unHideNotes \\startStaff  \\set Staff.forceClef = ##t \\bar "" \\set Staff.forceClef = ##t \\once \\override Staff.Clef.full-size-change = ##t \\clef " (d-GetPrevailingClef) " "))
    (d-DirectivePut-standalone-minpixels tag2 30)
    (d-DirectivePut-standalone-graphic tag1 "\n->\nDenemo\n48")
    (d-RefreshDisplay)
    (d-SetSaved #f))
