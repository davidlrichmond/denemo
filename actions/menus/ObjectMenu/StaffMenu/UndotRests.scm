;;;;;;;;UndotRests
(d-MoveToBeginning)
(let loop ()
    (if (and (Rest?) (positive? (d-GetDots)))
        (let ((num (d-GetDots)))
            (d-RemoveDot)
            (if (= num 2)
                (d-RemoveDot))
            (d-DuplicateRestNoteChord)
            (d-Diminish)
             (if (= num 2)
                (begin
                    (d-DuplicateRestNoteChord)
                    (d-Diminish)))))
            (if (d-NextChord)
                (loop)))