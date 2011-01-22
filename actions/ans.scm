(use-modules (srfi srfi-1))
(use-modules (srfi srfi-8))
(use-modules (srfi srfi-13))
(use-modules (ice-9 optargs))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;Abstract Note System for Denemo Version 3;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;by Nils Gey;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ANS makes it easy to calculate with notation while keeping in mind that
; there are basic note ("The White Keys") as well as sharp or flat notes
; and finally enharmonic notes (gisis) and all have to respect the key-
; signature or they are considered "alterated".
; Each note is represented by a number on which points to an
; absolute notename in Lilypond syntax This is especially desinged to 
; make diatonic shifting, real transpostion and other modifications more
; easy for script-authors. 
; System by Nils Gey 2010 (thanks to Till Hartmann for table generation)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;Beginning of Abstract Note System Version 3;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;by Nils Gey;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;0 - A tone humans cannot hear anymore.
;1420 - "Middle" c'
;2130 - Soprano-Singers high C
;3150 - Goes beyond the range of a modern piano
;+inf.0 - A rest

;<10 is reserved for microtones, in the future.
;+10 One accidental up jumps over to the next note after cisis 
;+50 One diatonic step, preserve accidentals
;+350 One Octave

(define ANS::NoteTable (make-hash-table 317))
(hashq-set! ANS::NoteTable 00 'ceses,,,)
(hashq-set! ANS::NoteTable 10 'ces,,,)
(hashq-set! ANS::NoteTable 20 'c,,,)
(hashq-set! ANS::NoteTable 30 'cis,,,)
(hashq-set! ANS::NoteTable 40 'cisis,,,)
(hashq-set! ANS::NoteTable 50 'deses,,,)
(hashq-set! ANS::NoteTable 60 'des,,,)
(hashq-set! ANS::NoteTable 70 'd,,,)
(hashq-set! ANS::NoteTable 80 'dis,,,)
(hashq-set! ANS::NoteTable 90 'disis,,,)
(hashq-set! ANS::NoteTable 100 'eeses,,,)
(hashq-set! ANS::NoteTable 110 'ees,,,)
(hashq-set! ANS::NoteTable 120 'e,,,)
(hashq-set! ANS::NoteTable 130 'eis,,,)
(hashq-set! ANS::NoteTable 140 'eisis,,,)
(hashq-set! ANS::NoteTable 150 'feses,,,)
(hashq-set! ANS::NoteTable 160 'fes,,,)
(hashq-set! ANS::NoteTable 170 'f,,,)
(hashq-set! ANS::NoteTable 180 'fis,,,)
(hashq-set! ANS::NoteTable 190 'fisis,,,)
(hashq-set! ANS::NoteTable 200 'geses,,,)
(hashq-set! ANS::NoteTable 210 'ges,,,)
(hashq-set! ANS::NoteTable 220 'g,,,)
(hashq-set! ANS::NoteTable 230 'gis,,,)
(hashq-set! ANS::NoteTable 240 'gisis,,,)
(hashq-set! ANS::NoteTable 250 'aeses,,,)
(hashq-set! ANS::NoteTable 260 'aes,,,)
(hashq-set! ANS::NoteTable 270 'a,,,)
(hashq-set! ANS::NoteTable 280 'ais,,,)
(hashq-set! ANS::NoteTable 290 'aisis,,,)
(hashq-set! ANS::NoteTable 300 'beses,,,)
(hashq-set! ANS::NoteTable 310 'bes,,,)
(hashq-set! ANS::NoteTable 320 'b,,,)
(hashq-set! ANS::NoteTable 330 'bis,,,)
(hashq-set! ANS::NoteTable 340 'bisis,,,)
(hashq-set! ANS::NoteTable 350 'ceses,,)
(hashq-set! ANS::NoteTable 360 'ces,,)
(hashq-set! ANS::NoteTable 370 'c,,)
(hashq-set! ANS::NoteTable 380 'cis,,)
(hashq-set! ANS::NoteTable 390 'cisis,,)
(hashq-set! ANS::NoteTable 400 'deses,,)
(hashq-set! ANS::NoteTable 410 'des,,)
(hashq-set! ANS::NoteTable 420 'd,,)
(hashq-set! ANS::NoteTable 430 'dis,,)
(hashq-set! ANS::NoteTable 440 'disis,,)
(hashq-set! ANS::NoteTable 450 'eeses,,)
(hashq-set! ANS::NoteTable 460 'ees,,)
(hashq-set! ANS::NoteTable 470 'e,,)
(hashq-set! ANS::NoteTable 480 'eis,,)
(hashq-set! ANS::NoteTable 490 'eisis,,)
(hashq-set! ANS::NoteTable 500 'feses,,)
(hashq-set! ANS::NoteTable 510 'fes,,)
(hashq-set! ANS::NoteTable 520 'f,,)
(hashq-set! ANS::NoteTable 530 'fis,,)
(hashq-set! ANS::NoteTable 540 'fisis,,)
(hashq-set! ANS::NoteTable 550 'geses,,)
(hashq-set! ANS::NoteTable 560 'ges,,)
(hashq-set! ANS::NoteTable 570 'g,,)
(hashq-set! ANS::NoteTable 580 'gis,,)
(hashq-set! ANS::NoteTable 590 'gisis,,)
(hashq-set! ANS::NoteTable 600 'aeses,,)
(hashq-set! ANS::NoteTable 610 'aes,,)
(hashq-set! ANS::NoteTable 620 'a,,)
(hashq-set! ANS::NoteTable 630 'ais,,)
(hashq-set! ANS::NoteTable 640 'aisis,,)
(hashq-set! ANS::NoteTable 650 'beses,,)
(hashq-set! ANS::NoteTable 660 'bes,,)
(hashq-set! ANS::NoteTable 670 'b,,)
(hashq-set! ANS::NoteTable 680 'bis,,)
(hashq-set! ANS::NoteTable 690 'bisis,,)
(hashq-set! ANS::NoteTable 700 'ceses,)
(hashq-set! ANS::NoteTable 710 'ces,)
(hashq-set! ANS::NoteTable 720 'c,)
(hashq-set! ANS::NoteTable 730 'cis,)
(hashq-set! ANS::NoteTable 740 'cisis,)
(hashq-set! ANS::NoteTable 750 'deses,)
(hashq-set! ANS::NoteTable 760 'des,)
(hashq-set! ANS::NoteTable 770 'd,)
(hashq-set! ANS::NoteTable 780 'dis,)
(hashq-set! ANS::NoteTable 790 'disis,)
(hashq-set! ANS::NoteTable 800 'eeses,)
(hashq-set! ANS::NoteTable 810 'ees,)
(hashq-set! ANS::NoteTable 820 'e,)
(hashq-set! ANS::NoteTable 830 'eis,)
(hashq-set! ANS::NoteTable 840 'eisis,)
(hashq-set! ANS::NoteTable 850 'feses,)
(hashq-set! ANS::NoteTable 860 'fes,)
(hashq-set! ANS::NoteTable 870 'f,)
(hashq-set! ANS::NoteTable 880 'fis,)
(hashq-set! ANS::NoteTable 890 'fisis,)
(hashq-set! ANS::NoteTable 900 'geses,)
(hashq-set! ANS::NoteTable 910 'ges,)
(hashq-set! ANS::NoteTable 920 'g,)
(hashq-set! ANS::NoteTable 930 'gis,)
(hashq-set! ANS::NoteTable 940 'gisis,)
(hashq-set! ANS::NoteTable 950 'aeses,)
(hashq-set! ANS::NoteTable 960 'aes,)
(hashq-set! ANS::NoteTable 970 'a,)
(hashq-set! ANS::NoteTable 980 'ais,)
(hashq-set! ANS::NoteTable 990 'aisis,)
(hashq-set! ANS::NoteTable 1000 'beses,)
(hashq-set! ANS::NoteTable 1010 'bes,)
(hashq-set! ANS::NoteTable 1020 'b,)
(hashq-set! ANS::NoteTable 1030 'bis,)
(hashq-set! ANS::NoteTable 1040 'bisis,)
(hashq-set! ANS::NoteTable 1050 'ceses)
(hashq-set! ANS::NoteTable 1060 'ces)
(hashq-set! ANS::NoteTable 1070 'c)
(hashq-set! ANS::NoteTable 1080 'cis)
(hashq-set! ANS::NoteTable 1090 'cisis)
(hashq-set! ANS::NoteTable 1100 'deses)
(hashq-set! ANS::NoteTable 1110 'des)
(hashq-set! ANS::NoteTable 1120 'd)
(hashq-set! ANS::NoteTable 1130 'dis)
(hashq-set! ANS::NoteTable 1140 'disis)
(hashq-set! ANS::NoteTable 1150 'eeses)
(hashq-set! ANS::NoteTable 1160 'ees)
(hashq-set! ANS::NoteTable 1170 'e)
(hashq-set! ANS::NoteTable 1180 'eis)
(hashq-set! ANS::NoteTable 1190 'eisis)
(hashq-set! ANS::NoteTable 1200 'feses)
(hashq-set! ANS::NoteTable 1210 'fes)
(hashq-set! ANS::NoteTable 1220 'f)
(hashq-set! ANS::NoteTable 1230 'fis)
(hashq-set! ANS::NoteTable 1240 'fisis)
(hashq-set! ANS::NoteTable 1250 'geses)
(hashq-set! ANS::NoteTable 1260 'ges)
(hashq-set! ANS::NoteTable 1270 'g)
(hashq-set! ANS::NoteTable 1280 'gis)
(hashq-set! ANS::NoteTable 1290 'gisis)
(hashq-set! ANS::NoteTable 1300 'aeses)
(hashq-set! ANS::NoteTable 1310 'aes)
(hashq-set! ANS::NoteTable 1320 'a)
(hashq-set! ANS::NoteTable 1330 'ais)
(hashq-set! ANS::NoteTable 1340 'aisis)
(hashq-set! ANS::NoteTable 1350 'beses)
(hashq-set! ANS::NoteTable 1360 'bes)
(hashq-set! ANS::NoteTable 1370 'b)
(hashq-set! ANS::NoteTable 1380 'bis)
(hashq-set! ANS::NoteTable 1390 'bisis)
(hashq-set! ANS::NoteTable 1400 'ceses')
(hashq-set! ANS::NoteTable 1410 'ces')
(hashq-set! ANS::NoteTable 1420 'c')
(hashq-set! ANS::NoteTable 1430 'cis')
(hashq-set! ANS::NoteTable 1440 'cisis')
(hashq-set! ANS::NoteTable 1450 'deses')
(hashq-set! ANS::NoteTable 1460 'des')
(hashq-set! ANS::NoteTable 1470 'd')
(hashq-set! ANS::NoteTable 1480 'dis')
(hashq-set! ANS::NoteTable 1490 'disis')
(hashq-set! ANS::NoteTable 1500 'eeses')
(hashq-set! ANS::NoteTable 1510 'ees')
(hashq-set! ANS::NoteTable 1520 'e')
(hashq-set! ANS::NoteTable 1530 'eis')
(hashq-set! ANS::NoteTable 1540 'eisis')
(hashq-set! ANS::NoteTable 1550 'feses')
(hashq-set! ANS::NoteTable 1560 'fes')
(hashq-set! ANS::NoteTable 1570 'f')
(hashq-set! ANS::NoteTable 1580 'fis')
(hashq-set! ANS::NoteTable 1590 'fisis')
(hashq-set! ANS::NoteTable 1600 'geses')
(hashq-set! ANS::NoteTable 1610 'ges')
(hashq-set! ANS::NoteTable 1620 'g')
(hashq-set! ANS::NoteTable 1630 'gis')
(hashq-set! ANS::NoteTable 1640 'gisis')
(hashq-set! ANS::NoteTable 1650 'aeses')
(hashq-set! ANS::NoteTable 1660 'aes')
(hashq-set! ANS::NoteTable 1670 'a')
(hashq-set! ANS::NoteTable 1680 'ais')
(hashq-set! ANS::NoteTable 1690 'aisis')
(hashq-set! ANS::NoteTable 1700 'beses')
(hashq-set! ANS::NoteTable 1710 'bes')
(hashq-set! ANS::NoteTable 1720 'b')
(hashq-set! ANS::NoteTable 1730 'bis')
(hashq-set! ANS::NoteTable 1740 'bisis')
(hashq-set! ANS::NoteTable 1750 'ceses'')
(hashq-set! ANS::NoteTable 1760 'ces'')
(hashq-set! ANS::NoteTable 1770 'c'')
(hashq-set! ANS::NoteTable 1780 'cis'')
(hashq-set! ANS::NoteTable 1790 'cisis'')
(hashq-set! ANS::NoteTable 1800 'deses'')
(hashq-set! ANS::NoteTable 1810 'des'')
(hashq-set! ANS::NoteTable 1820 'd'')
(hashq-set! ANS::NoteTable 1830 'dis'')
(hashq-set! ANS::NoteTable 1840 'disis'')
(hashq-set! ANS::NoteTable 1850 'eeses'')
(hashq-set! ANS::NoteTable 1860 'ees'')
(hashq-set! ANS::NoteTable 1870 'e'')
(hashq-set! ANS::NoteTable 1880 'eis'')
(hashq-set! ANS::NoteTable 1890 'eisis'')
(hashq-set! ANS::NoteTable 1900 'feses'')
(hashq-set! ANS::NoteTable 1910 'fes'')
(hashq-set! ANS::NoteTable 1920 'f'')
(hashq-set! ANS::NoteTable 1930 'fis'')
(hashq-set! ANS::NoteTable 1940 'fisis'')
(hashq-set! ANS::NoteTable 1950 'geses'')
(hashq-set! ANS::NoteTable 1960 'ges'')
(hashq-set! ANS::NoteTable 1970 'g'')
(hashq-set! ANS::NoteTable 1980 'gis'')
(hashq-set! ANS::NoteTable 1990 'gisis'')
(hashq-set! ANS::NoteTable 2000 'aeses'')
(hashq-set! ANS::NoteTable 2010 'aes'')
(hashq-set! ANS::NoteTable 2020 'a'')
(hashq-set! ANS::NoteTable 2030 'ais'')
(hashq-set! ANS::NoteTable 2040 'aisis'')
(hashq-set! ANS::NoteTable 2050 'beses'')
(hashq-set! ANS::NoteTable 2060 'bes'')
(hashq-set! ANS::NoteTable 2070 'b'')
(hashq-set! ANS::NoteTable 2080 'bis'')
(hashq-set! ANS::NoteTable 2090 'bisis'')
(hashq-set! ANS::NoteTable 2100 'ceses''')
(hashq-set! ANS::NoteTable 2110 'ces''')
(hashq-set! ANS::NoteTable 2120 'c''')
(hashq-set! ANS::NoteTable 2130 'cis''')
(hashq-set! ANS::NoteTable 2140 'cisis''')
(hashq-set! ANS::NoteTable 2150 'deses''')
(hashq-set! ANS::NoteTable 2160 'des''')
(hashq-set! ANS::NoteTable 2170 'd''')
(hashq-set! ANS::NoteTable 2180 'dis''')
(hashq-set! ANS::NoteTable 2190 'disis''')
(hashq-set! ANS::NoteTable 2200 'eeses''')
(hashq-set! ANS::NoteTable 2210 'ees''')
(hashq-set! ANS::NoteTable 2220 'e''')
(hashq-set! ANS::NoteTable 2230 'eis''')
(hashq-set! ANS::NoteTable 2240 'eisis''')
(hashq-set! ANS::NoteTable 2250 'feses''')
(hashq-set! ANS::NoteTable 2260 'fes''')
(hashq-set! ANS::NoteTable 2270 'f''')
(hashq-set! ANS::NoteTable 2280 'fis''')
(hashq-set! ANS::NoteTable 2290 'fisis''')
(hashq-set! ANS::NoteTable 2300 'geses''')
(hashq-set! ANS::NoteTable 2310 'ges''')
(hashq-set! ANS::NoteTable 2320 'g''')
(hashq-set! ANS::NoteTable 2330 'gis''')
(hashq-set! ANS::NoteTable 2340 'gisis''')
(hashq-set! ANS::NoteTable 2350 'aeses''')
(hashq-set! ANS::NoteTable 2360 'aes''')
(hashq-set! ANS::NoteTable 2370 'a''')
(hashq-set! ANS::NoteTable 2380 'ais''')
(hashq-set! ANS::NoteTable 2390 'aisis''')
(hashq-set! ANS::NoteTable 2400 'beses''')
(hashq-set! ANS::NoteTable 2410 'bes''')
(hashq-set! ANS::NoteTable 2420 'b''')
(hashq-set! ANS::NoteTable 2430 'bis''')
(hashq-set! ANS::NoteTable 2440 'bisis''')
(hashq-set! ANS::NoteTable 2450 'ceses'''')
(hashq-set! ANS::NoteTable 2460 'ces'''')
(hashq-set! ANS::NoteTable 2470 'c'''')
(hashq-set! ANS::NoteTable 2480 'cis'''')
(hashq-set! ANS::NoteTable 2490 'cisis'''')
(hashq-set! ANS::NoteTable 2500 'deses'''')
(hashq-set! ANS::NoteTable 2510 'des'''')
(hashq-set! ANS::NoteTable 2520 'd'''')
(hashq-set! ANS::NoteTable 2530 'dis'''')
(hashq-set! ANS::NoteTable 2540 'disis'''')
(hashq-set! ANS::NoteTable 2550 'eeses'''')
(hashq-set! ANS::NoteTable 2560 'ees'''')
(hashq-set! ANS::NoteTable 2570 'e'''')
(hashq-set! ANS::NoteTable 2580 'eis'''')
(hashq-set! ANS::NoteTable 2590 'eisis'''')
(hashq-set! ANS::NoteTable 2600 'feses'''')
(hashq-set! ANS::NoteTable 2610 'fes'''')
(hashq-set! ANS::NoteTable 2620 'f'''')
(hashq-set! ANS::NoteTable 2630 'fis'''')
(hashq-set! ANS::NoteTable 2640 'fisis'''')
(hashq-set! ANS::NoteTable 2650 'geses'''')
(hashq-set! ANS::NoteTable 2660 'ges'''')
(hashq-set! ANS::NoteTable 2670 'g'''')
(hashq-set! ANS::NoteTable 2680 'gis'''')
(hashq-set! ANS::NoteTable 2690 'gisis'''')
(hashq-set! ANS::NoteTable 2700 'aeses'''')
(hashq-set! ANS::NoteTable 2710 'aes'''')
(hashq-set! ANS::NoteTable 2720 'a'''')
(hashq-set! ANS::NoteTable 2730 'ais'''')
(hashq-set! ANS::NoteTable 2740 'aisis'''')
(hashq-set! ANS::NoteTable 2750 'beses'''')
(hashq-set! ANS::NoteTable 2760 'bes'''')
(hashq-set! ANS::NoteTable 2770 'b'''')
(hashq-set! ANS::NoteTable 2780 'bis'''')
(hashq-set! ANS::NoteTable 2790 'bisis'''')
(hashq-set! ANS::NoteTable 2800 'ceses''''')
(hashq-set! ANS::NoteTable 2810 'ces''''')
(hashq-set! ANS::NoteTable 2820 'c''''')
(hashq-set! ANS::NoteTable 2830 'cis''''')
(hashq-set! ANS::NoteTable 2840 'cisis''''')
(hashq-set! ANS::NoteTable 2850 'deses''''')
(hashq-set! ANS::NoteTable 2860 'des''''')
(hashq-set! ANS::NoteTable 2870 'd''''')
(hashq-set! ANS::NoteTable 2880 'dis''''')
(hashq-set! ANS::NoteTable 2890 'disis''''')
(hashq-set! ANS::NoteTable 2900 'eeses''''')
(hashq-set! ANS::NoteTable 2910 'ees''''')
(hashq-set! ANS::NoteTable 2920 'e''''')
(hashq-set! ANS::NoteTable 2930 'eis''''')
(hashq-set! ANS::NoteTable 2940 'eisis''''')
(hashq-set! ANS::NoteTable 2950 'feses''''')
(hashq-set! ANS::NoteTable 2960 'fes''''')
(hashq-set! ANS::NoteTable 2970 'f''''')
(hashq-set! ANS::NoteTable 2980 'fis''''')
(hashq-set! ANS::NoteTable 2990 'fisis''''')
(hashq-set! ANS::NoteTable 3000 'geses''''')
(hashq-set! ANS::NoteTable 3010 'ges''''')
(hashq-set! ANS::NoteTable 3020 'g''''')
(hashq-set! ANS::NoteTable 3030 'gis''''')
(hashq-set! ANS::NoteTable 3040 'gisis''''')
(hashq-set! ANS::NoteTable 3050 'aeses''''')
(hashq-set! ANS::NoteTable 3060 'aes''''')
(hashq-set! ANS::NoteTable 3070 'a''''')
(hashq-set! ANS::NoteTable 3080 'ais''''')
(hashq-set! ANS::NoteTable 3090 'aisis''''')
(hashq-set! ANS::NoteTable 3100 'beses''''')
(hashq-set! ANS::NoteTable 3110 'bes''''')
(hashq-set! ANS::NoteTable 3120 'b''''')
(hashq-set! ANS::NoteTable 3130 'bis''''')
(hashq-set! ANS::NoteTable 3140 'bisis''''')
(hashq-set! ANS::NoteTable +inf.0 'r)

;;;; Reverse Assignments
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define ANS::NoteTableR (make-hash-table 317))
(hashq-set! ANS::NoteTableR 'ceses,,, 00)
(hashq-set! ANS::NoteTableR 'ces,,, 10)
(hashq-set! ANS::NoteTableR 'c,,, 20)
(hashq-set! ANS::NoteTableR 'cis,,, 30)
(hashq-set! ANS::NoteTableR 'cisis,,, 40)
(hashq-set! ANS::NoteTableR 'deses,,, 50)
(hashq-set! ANS::NoteTableR 'des,,, 60)
(hashq-set! ANS::NoteTableR 'd,,, 70)
(hashq-set! ANS::NoteTableR 'dis,,, 80)
(hashq-set! ANS::NoteTableR 'disis,,, 90)
(hashq-set! ANS::NoteTableR 'eeses,,, 100)
(hashq-set! ANS::NoteTableR 'ees,,, 110)
(hashq-set! ANS::NoteTableR 'e,,, 120)
(hashq-set! ANS::NoteTableR 'eis,,, 130)
(hashq-set! ANS::NoteTableR 'eisis,,, 140)
(hashq-set! ANS::NoteTableR 'feses,,, 150)
(hashq-set! ANS::NoteTableR 'fes,,, 160)
(hashq-set! ANS::NoteTableR 'f,,, 170)
(hashq-set! ANS::NoteTableR 'fis,,, 180)
(hashq-set! ANS::NoteTableR 'fisis,,, 190)
(hashq-set! ANS::NoteTableR 'geses,,, 200)
(hashq-set! ANS::NoteTableR 'ges,,, 210)
(hashq-set! ANS::NoteTableR 'g,,, 220)
(hashq-set! ANS::NoteTableR 'gis,,, 230)
(hashq-set! ANS::NoteTableR 'gisis,,, 240)
(hashq-set! ANS::NoteTableR 'aeses,,, 250)
(hashq-set! ANS::NoteTableR 'aes,,, 260)
(hashq-set! ANS::NoteTableR 'a,,, 270)
(hashq-set! ANS::NoteTableR 'ais,,, 280)
(hashq-set! ANS::NoteTableR 'aisis,,, 290)
(hashq-set! ANS::NoteTableR 'beses,,, 300)
(hashq-set! ANS::NoteTableR 'bes,,, 310)
(hashq-set! ANS::NoteTableR 'b,,, 320)
(hashq-set! ANS::NoteTableR 'bis,,, 330)
(hashq-set! ANS::NoteTableR 'bisis,,, 340)
(hashq-set! ANS::NoteTableR 'ceses,, 350)
(hashq-set! ANS::NoteTableR 'ces,, 360)
(hashq-set! ANS::NoteTableR 'c,, 370)
(hashq-set! ANS::NoteTableR 'cis,, 380)
(hashq-set! ANS::NoteTableR 'cisis,, 390)
(hashq-set! ANS::NoteTableR 'deses,, 400)
(hashq-set! ANS::NoteTableR 'des,, 410)
(hashq-set! ANS::NoteTableR 'd,, 420)
(hashq-set! ANS::NoteTableR 'dis,, 430)
(hashq-set! ANS::NoteTableR 'disis,, 440)
(hashq-set! ANS::NoteTableR 'eeses,, 450)
(hashq-set! ANS::NoteTableR 'ees,, 460)
(hashq-set! ANS::NoteTableR 'e,, 470)
(hashq-set! ANS::NoteTableR 'eis,, 480)
(hashq-set! ANS::NoteTableR 'eisis,, 490)
(hashq-set! ANS::NoteTableR 'feses,, 500)
(hashq-set! ANS::NoteTableR 'fes,, 510)
(hashq-set! ANS::NoteTableR 'f,, 520)
(hashq-set! ANS::NoteTableR 'fis,, 530)
(hashq-set! ANS::NoteTableR 'fisis,, 540)
(hashq-set! ANS::NoteTableR 'geses,, 550)
(hashq-set! ANS::NoteTableR 'ges,, 560)
(hashq-set! ANS::NoteTableR 'g,, 570)
(hashq-set! ANS::NoteTableR 'gis,, 580)
(hashq-set! ANS::NoteTableR 'gisis,, 590)
(hashq-set! ANS::NoteTableR 'aeses,, 600)
(hashq-set! ANS::NoteTableR 'aes,, 610)
(hashq-set! ANS::NoteTableR 'a,, 620)
(hashq-set! ANS::NoteTableR 'ais,, 630)
(hashq-set! ANS::NoteTableR 'aisis,, 640)
(hashq-set! ANS::NoteTableR 'beses,, 650)
(hashq-set! ANS::NoteTableR 'bes,, 660)
(hashq-set! ANS::NoteTableR 'b,, 670)
(hashq-set! ANS::NoteTableR 'bis,, 680)
(hashq-set! ANS::NoteTableR 'bisis,, 690)
(hashq-set! ANS::NoteTableR 'ceses, 700)
(hashq-set! ANS::NoteTableR 'ces, 710)
(hashq-set! ANS::NoteTableR 'c, 720)
(hashq-set! ANS::NoteTableR 'cis, 730)
(hashq-set! ANS::NoteTableR 'cisis, 740)
(hashq-set! ANS::NoteTableR 'deses, 750)
(hashq-set! ANS::NoteTableR 'des, 760)
(hashq-set! ANS::NoteTableR 'd, 770)
(hashq-set! ANS::NoteTableR 'dis, 780)
(hashq-set! ANS::NoteTableR 'disis, 790)
(hashq-set! ANS::NoteTableR 'eeses, 800)
(hashq-set! ANS::NoteTableR 'ees, 810)
(hashq-set! ANS::NoteTableR 'e, 820)
(hashq-set! ANS::NoteTableR 'eis, 830)
(hashq-set! ANS::NoteTableR 'eisis, 840)
(hashq-set! ANS::NoteTableR 'feses, 850)
(hashq-set! ANS::NoteTableR 'fes, 860)
(hashq-set! ANS::NoteTableR 'f, 870)
(hashq-set! ANS::NoteTableR 'fis, 880)
(hashq-set! ANS::NoteTableR 'fisis, 890)
(hashq-set! ANS::NoteTableR 'geses, 900)
(hashq-set! ANS::NoteTableR 'ges, 910)
(hashq-set! ANS::NoteTableR 'g, 920)
(hashq-set! ANS::NoteTableR 'gis, 930)
(hashq-set! ANS::NoteTableR 'gisis, 940)
(hashq-set! ANS::NoteTableR 'aeses, 950)
(hashq-set! ANS::NoteTableR 'aes, 960)
(hashq-set! ANS::NoteTableR 'a, 970)
(hashq-set! ANS::NoteTableR 'ais, 980)
(hashq-set! ANS::NoteTableR 'aisis, 990)
(hashq-set! ANS::NoteTableR 'beses, 1000)
(hashq-set! ANS::NoteTableR 'bes, 1010)
(hashq-set! ANS::NoteTableR 'b, 1020)
(hashq-set! ANS::NoteTableR 'bis, 1030)
(hashq-set! ANS::NoteTableR 'bisis, 1040)
(hashq-set! ANS::NoteTableR 'ceses 1050)
(hashq-set! ANS::NoteTableR 'ces 1060)
(hashq-set! ANS::NoteTableR 'c 1070)
(hashq-set! ANS::NoteTableR 'cis 1080)
(hashq-set! ANS::NoteTableR 'cisis 1090)
(hashq-set! ANS::NoteTableR 'deses 1100)
(hashq-set! ANS::NoteTableR 'des 1110)
(hashq-set! ANS::NoteTableR 'd 1120)
(hashq-set! ANS::NoteTableR 'dis 1130)
(hashq-set! ANS::NoteTableR 'disis 1140)
(hashq-set! ANS::NoteTableR 'eeses 1150)
(hashq-set! ANS::NoteTableR 'ees 1160)
(hashq-set! ANS::NoteTableR 'e 1170)
(hashq-set! ANS::NoteTableR 'eis 1180)
(hashq-set! ANS::NoteTableR 'eisis 1190)
(hashq-set! ANS::NoteTableR 'feses 1200)
(hashq-set! ANS::NoteTableR 'fes 1210)
(hashq-set! ANS::NoteTableR 'f 1220)
(hashq-set! ANS::NoteTableR 'fis 1230)
(hashq-set! ANS::NoteTableR 'fisis 1240)
(hashq-set! ANS::NoteTableR 'geses 1250)
(hashq-set! ANS::NoteTableR 'ges 1260)
(hashq-set! ANS::NoteTableR 'g 1270)
(hashq-set! ANS::NoteTableR 'gis 1280)
(hashq-set! ANS::NoteTableR 'gisis 1290)
(hashq-set! ANS::NoteTableR 'aeses 1300)
(hashq-set! ANS::NoteTableR 'aes 1310)
(hashq-set! ANS::NoteTableR 'a 1320)
(hashq-set! ANS::NoteTableR 'ais 1330)
(hashq-set! ANS::NoteTableR 'aisis 1340)
(hashq-set! ANS::NoteTableR 'beses 1350)
(hashq-set! ANS::NoteTableR 'bes 1360)
(hashq-set! ANS::NoteTableR 'b 1370)
(hashq-set! ANS::NoteTableR 'bis 1380)
(hashq-set! ANS::NoteTableR 'bisis 1390)
(hashq-set! ANS::NoteTableR 'ceses' 1400)
(hashq-set! ANS::NoteTableR 'ces' 1410)
(hashq-set! ANS::NoteTableR 'c' 1420)
(hashq-set! ANS::NoteTableR 'cis' 1430)
(hashq-set! ANS::NoteTableR 'cisis' 1440)
(hashq-set! ANS::NoteTableR 'deses' 1450)
(hashq-set! ANS::NoteTableR 'des' 1460)
(hashq-set! ANS::NoteTableR 'd' 1470)
(hashq-set! ANS::NoteTableR 'dis' 1480)
(hashq-set! ANS::NoteTableR 'disis' 1490)
(hashq-set! ANS::NoteTableR 'eeses' 1500)
(hashq-set! ANS::NoteTableR 'ees' 1510)
(hashq-set! ANS::NoteTableR 'e' 1520)
(hashq-set! ANS::NoteTableR 'eis' 1530)
(hashq-set! ANS::NoteTableR 'eisis' 1540)
(hashq-set! ANS::NoteTableR 'feses' 1550)
(hashq-set! ANS::NoteTableR 'fes' 1560)
(hashq-set! ANS::NoteTableR 'f' 1570)
(hashq-set! ANS::NoteTableR 'fis' 1580)
(hashq-set! ANS::NoteTableR 'fisis' 1590)
(hashq-set! ANS::NoteTableR 'geses' 1600)
(hashq-set! ANS::NoteTableR 'ges' 1610)
(hashq-set! ANS::NoteTableR 'g' 1620)
(hashq-set! ANS::NoteTableR 'gis' 1630)
(hashq-set! ANS::NoteTableR 'gisis' 1640)
(hashq-set! ANS::NoteTableR 'aeses' 1650)
(hashq-set! ANS::NoteTableR 'aes' 1660)
(hashq-set! ANS::NoteTableR 'a' 1670)
(hashq-set! ANS::NoteTableR 'ais' 1680)
(hashq-set! ANS::NoteTableR 'aisis' 1690)
(hashq-set! ANS::NoteTableR 'beses' 1700)
(hashq-set! ANS::NoteTableR 'bes' 1710)
(hashq-set! ANS::NoteTableR 'b' 1720)
(hashq-set! ANS::NoteTableR 'bis' 1730)
(hashq-set! ANS::NoteTableR 'bisis' 1740)
(hashq-set! ANS::NoteTableR 'ceses'' 1750)
(hashq-set! ANS::NoteTableR 'ces'' 1760)
(hashq-set! ANS::NoteTableR 'c'' 1770)
(hashq-set! ANS::NoteTableR 'cis'' 1780)
(hashq-set! ANS::NoteTableR 'cisis'' 1790)
(hashq-set! ANS::NoteTableR 'deses'' 1800)
(hashq-set! ANS::NoteTableR 'des'' 1810)
(hashq-set! ANS::NoteTableR 'd'' 1820)
(hashq-set! ANS::NoteTableR 'dis'' 1830)
(hashq-set! ANS::NoteTableR 'disis'' 1840)
(hashq-set! ANS::NoteTableR 'eeses'' 1850)
(hashq-set! ANS::NoteTableR 'ees'' 1860)
(hashq-set! ANS::NoteTableR 'e'' 1870)
(hashq-set! ANS::NoteTableR 'eis'' 1880)
(hashq-set! ANS::NoteTableR 'eisis'' 1890)
(hashq-set! ANS::NoteTableR 'feses'' 1900)
(hashq-set! ANS::NoteTableR 'fes'' 1910)
(hashq-set! ANS::NoteTableR 'f'' 1920)
(hashq-set! ANS::NoteTableR 'fis'' 1930)
(hashq-set! ANS::NoteTableR 'fisis'' 1940)
(hashq-set! ANS::NoteTableR 'geses'' 1950)
(hashq-set! ANS::NoteTableR 'ges'' 1960)
(hashq-set! ANS::NoteTableR 'g'' 1970)
(hashq-set! ANS::NoteTableR 'gis'' 1980)
(hashq-set! ANS::NoteTableR 'gisis'' 1990)
(hashq-set! ANS::NoteTableR 'aeses'' 2000)
(hashq-set! ANS::NoteTableR 'aes'' 2010)
(hashq-set! ANS::NoteTableR 'a'' 2020)
(hashq-set! ANS::NoteTableR 'ais'' 2030)
(hashq-set! ANS::NoteTableR 'aisis'' 2040)
(hashq-set! ANS::NoteTableR 'beses'' 2050)
(hashq-set! ANS::NoteTableR 'bes'' 2060)
(hashq-set! ANS::NoteTableR 'b'' 2070)
(hashq-set! ANS::NoteTableR 'bis'' 2080)
(hashq-set! ANS::NoteTableR 'bisis'' 2090)
(hashq-set! ANS::NoteTableR 'ceses''' 2100)
(hashq-set! ANS::NoteTableR 'ces''' 2110)
(hashq-set! ANS::NoteTableR 'c''' 2120)
(hashq-set! ANS::NoteTableR 'cis''' 2130)
(hashq-set! ANS::NoteTableR 'cisis''' 2140)
(hashq-set! ANS::NoteTableR 'deses''' 2150)
(hashq-set! ANS::NoteTableR 'des''' 2160)
(hashq-set! ANS::NoteTableR 'd''' 2170)
(hashq-set! ANS::NoteTableR 'dis''' 2180)
(hashq-set! ANS::NoteTableR 'disis''' 2190)
(hashq-set! ANS::NoteTableR 'eeses''' 2200)
(hashq-set! ANS::NoteTableR 'ees''' 2210)
(hashq-set! ANS::NoteTableR 'e''' 2220)
(hashq-set! ANS::NoteTableR 'eis''' 2230)
(hashq-set! ANS::NoteTableR 'eisis''' 2240)
(hashq-set! ANS::NoteTableR 'feses''' 2250)
(hashq-set! ANS::NoteTableR 'fes''' 2260)
(hashq-set! ANS::NoteTableR 'f''' 2270)
(hashq-set! ANS::NoteTableR 'fis''' 2280)
(hashq-set! ANS::NoteTableR 'fisis''' 2290)
(hashq-set! ANS::NoteTableR 'geses''' 2300)
(hashq-set! ANS::NoteTableR 'ges''' 2310)
(hashq-set! ANS::NoteTableR 'g''' 2320)
(hashq-set! ANS::NoteTableR 'gis''' 2330)
(hashq-set! ANS::NoteTableR 'gisis''' 2340)
(hashq-set! ANS::NoteTableR 'aeses''' 2350)
(hashq-set! ANS::NoteTableR 'aes''' 2360)
(hashq-set! ANS::NoteTableR 'a''' 2370)
(hashq-set! ANS::NoteTableR 'ais''' 2380)
(hashq-set! ANS::NoteTableR 'aisis''' 2390)
(hashq-set! ANS::NoteTableR 'beses''' 2400)
(hashq-set! ANS::NoteTableR 'bes''' 2410)
(hashq-set! ANS::NoteTableR 'b''' 2420)
(hashq-set! ANS::NoteTableR 'bis''' 2430)
(hashq-set! ANS::NoteTableR 'bisis''' 2440)
(hashq-set! ANS::NoteTableR 'ceses'''' 2450)
(hashq-set! ANS::NoteTableR 'ces'''' 2460)
(hashq-set! ANS::NoteTableR 'c'''' 2470)
(hashq-set! ANS::NoteTableR 'cis'''' 2480)
(hashq-set! ANS::NoteTableR 'cisis'''' 2490)
(hashq-set! ANS::NoteTableR 'deses'''' 2500)
(hashq-set! ANS::NoteTableR 'des'''' 2510)
(hashq-set! ANS::NoteTableR 'd'''' 2520)
(hashq-set! ANS::NoteTableR 'dis'''' 2530)
(hashq-set! ANS::NoteTableR 'disis'''' 2540)
(hashq-set! ANS::NoteTableR 'eeses'''' 2550)
(hashq-set! ANS::NoteTableR 'ees'''' 2560)
(hashq-set! ANS::NoteTableR 'e'''' 2570)
(hashq-set! ANS::NoteTableR 'eis'''' 2580)
(hashq-set! ANS::NoteTableR 'eisis'''' 2590)
(hashq-set! ANS::NoteTableR 'feses'''' 2600)
(hashq-set! ANS::NoteTableR 'fes'''' 2610)
(hashq-set! ANS::NoteTableR 'f'''' 2620)
(hashq-set! ANS::NoteTableR 'fis'''' 2630)
(hashq-set! ANS::NoteTableR 'fisis'''' 2640)
(hashq-set! ANS::NoteTableR 'geses'''' 2650)
(hashq-set! ANS::NoteTableR 'ges'''' 2660)
(hashq-set! ANS::NoteTableR 'g'''' 2670)
(hashq-set! ANS::NoteTableR 'gis'''' 2680)
(hashq-set! ANS::NoteTableR 'gisis'''' 2690)
(hashq-set! ANS::NoteTableR 'aeses'''' 2700)
(hashq-set! ANS::NoteTableR 'aes'''' 2710)
(hashq-set! ANS::NoteTableR 'a'''' 2720)
(hashq-set! ANS::NoteTableR 'ais'''' 2730)
(hashq-set! ANS::NoteTableR 'aisis'''' 2740)
(hashq-set! ANS::NoteTableR 'beses'''' 2750)
(hashq-set! ANS::NoteTableR 'bes'''' 2760)
(hashq-set! ANS::NoteTableR 'b'''' 2770)
(hashq-set! ANS::NoteTableR 'bis'''' 2780)
(hashq-set! ANS::NoteTableR 'bisis'''' 2790)
(hashq-set! ANS::NoteTableR 'ceses''''' 2800)
(hashq-set! ANS::NoteTableR 'ces''''' 2810)
(hashq-set! ANS::NoteTableR 'c''''' 2820)
(hashq-set! ANS::NoteTableR 'cis''''' 2830)
(hashq-set! ANS::NoteTableR 'cisis''''' 2840)
(hashq-set! ANS::NoteTableR 'deses''''' 2850)
(hashq-set! ANS::NoteTableR 'des''''' 2860)
(hashq-set! ANS::NoteTableR 'd''''' 2870)
(hashq-set! ANS::NoteTableR 'dis''''' 2880)
(hashq-set! ANS::NoteTableR 'disis''''' 2890)
(hashq-set! ANS::NoteTableR 'eeses''''' 2900)
(hashq-set! ANS::NoteTableR 'ees''''' 2910)
(hashq-set! ANS::NoteTableR 'e''''' 2920)
(hashq-set! ANS::NoteTableR 'eis''''' 2930)
(hashq-set! ANS::NoteTableR 'eisis''''' 2940)
(hashq-set! ANS::NoteTableR 'feses''''' 2950)
(hashq-set! ANS::NoteTableR 'fes''''' 2960)
(hashq-set! ANS::NoteTableR 'f''''' 2970)
(hashq-set! ANS::NoteTableR 'fis''''' 2980)
(hashq-set! ANS::NoteTableR 'fisis''''' 2990)
(hashq-set! ANS::NoteTableR 'geses''''' 3000)
(hashq-set! ANS::NoteTableR 'ges''''' 3010)
(hashq-set! ANS::NoteTableR 'g''''' 3020)
(hashq-set! ANS::NoteTableR 'gis''''' 3030)
(hashq-set! ANS::NoteTableR 'gisis''''' 3040)
(hashq-set! ANS::NoteTableR 'aeses''''' 3050)
(hashq-set! ANS::NoteTableR 'aes''''' 3060)
(hashq-set! ANS::NoteTableR 'a''''' 3070)
(hashq-set! ANS::NoteTableR 'ais''''' 3080)
(hashq-set! ANS::NoteTableR 'aisis''''' 3090)
(hashq-set! ANS::NoteTableR 'beses''''' 3100)
(hashq-set! ANS::NoteTableR 'bes''''' 3110)
(hashq-set! ANS::NoteTableR 'b''''' 3120)
(hashq-set! ANS::NoteTableR 'bis''''' 3130)
(hashq-set! ANS::NoteTableR 'bisis''''' 3140)
(hashq-set! ANS::NoteTableR 'r +inf.0)

;;;; The pillar of filth
;;;; To calculate real and correct intervals you need the pillar of fifth with 35 steps for each realistic notename (and 4 unrealistic ones)
;;;;;;;;;;;;;;;;;;;;;;;;
; First the index where a notename/ANS value can be found in the pillar, which is actually a list.
; Strange pattern. it starts with 150 then for all bb its -150, +200. The transition to single b its only -140, then -150 +200 again! 140 must be the b/f change.
(define ANS::PillarOfFifthIndex (make-hash-table))
	(hashq-set! ANS::PillarOfFifthIndex 150 0) ;feses
	(hashq-set! ANS::PillarOfFifthIndex 0 1) ;ceses
	(hashq-set! ANS::PillarOfFifthIndex 200 2) ;geses	
	(hashq-set! ANS::PillarOfFifthIndex 50  3) ;deses
	(hashq-set! ANS::PillarOfFifthIndex 250 4) ;aeses
	(hashq-set! ANS::PillarOfFifthIndex 100 5) ;eeses
	(hashq-set! ANS::PillarOfFifthIndex 300 6) ;beses 
	(hashq-set! ANS::PillarOfFifthIndex 160 7) ;fes
	(hashq-set! ANS::PillarOfFifthIndex 10 8) ;ces
	(hashq-set! ANS::PillarOfFifthIndex 210 9) ;ges
	(hashq-set! ANS::PillarOfFifthIndex 60 10) ;des
	(hashq-set! ANS::PillarOfFifthIndex 260 11) ;aes
	(hashq-set! ANS::PillarOfFifthIndex 110 12) ;ees
	(hashq-set! ANS::PillarOfFifthIndex 310 13) ;bes
	(hashq-set! ANS::PillarOfFifthIndex 170 14) ;f
	(hashq-set! ANS::PillarOfFifthIndex 20 15) ;c
	(hashq-set! ANS::PillarOfFifthIndex 220 16) ;g
	(hashq-set! ANS::PillarOfFifthIndex 70 17) ;d
	(hashq-set! ANS::PillarOfFifthIndex 270 18) ;a
	(hashq-set! ANS::PillarOfFifthIndex 120 19) ;e
	(hashq-set! ANS::PillarOfFifthIndex 320 20) ;b
	(hashq-set! ANS::PillarOfFifthIndex 180 21) ;fis
	(hashq-set! ANS::PillarOfFifthIndex 30 22) ;cis
	(hashq-set! ANS::PillarOfFifthIndex 230 23) ;gis
	(hashq-set! ANS::PillarOfFifthIndex 80 24) ;dis
	(hashq-set! ANS::PillarOfFifthIndex 280 25) ;ais
	(hashq-set! ANS::PillarOfFifthIndex 130 26) ;eis
	(hashq-set! ANS::PillarOfFifthIndex 330 27) ;bis
	(hashq-set! ANS::PillarOfFifthIndex 190 28) ;fisis
	(hashq-set! ANS::PillarOfFifthIndex 40 29) ;cisis
	(hashq-set! ANS::PillarOfFifthIndex 240 30) ;gisis
	(hashq-set! ANS::PillarOfFifthIndex 90 31) ;disis
	(hashq-set! ANS::PillarOfFifthIndex 290 32) ;aisis
	(hashq-set! ANS::PillarOfFifthIndex 140 33) ;eisis	
	(hashq-set! ANS::PillarOfFifthIndex 340 34) ;bisis


;The list is the actual pillar of fifth. Stepping left and right can be done by calculating a list-ref index value.	
(define ANS::PillarOfFifth 
 (list 
	150 ;feses	0
	0 ;ceses	1
	200 ;geses	2
	50 ;deses	3
	250 ;aeses	4
	100 ;eeses	5
	300 ;beses 	6
	160 ;fes	7
	10 ;ces		8
	210 ;ges	9
	60 ;des		10
	260 ;aes	11
	110 ;ees	12
	310 ;bes	13
	170 ;f		14
	20 ;c		15
	220 ;g		16
	70 ;d		17
	270 ;a		19
	120 ;e		20
	320 ;b		21
	180 ;fis	22
	30 ;cis		23
	230 ;gis	24
	80 ;dis		25
	280 ;ais	26
	130 ;eis	27
	330 ;bis	28
	190 ;fisis	29
	40 ;cisis	30
	240 ;gisis	31
	90 ;disis	32
	290 ;aisis	33
	140 ;eisis	34
	340 ;bisis	35
 )
)

; A table to translate the human readable "m2" for minor second into steps of fifth left or right in the pillar.
; TODO: Augmented and Diminished intervals, octave and >octave. For octaves it will return the same note again, so that must be passt to the calcUp and downFunctions. Maybe don't even do octaves here.
; TODO: this function only should be for < octave. Octave is more easy to do with CalcUp/Down followed by octave up/down
(define (ANS::IntervalGetSteps target)
	(cond
		((or (eq? target 'p1) (eq? target 'P1)) 0)			
		((eq? target 'm2) -5)			
		((eq? target 'M2) 2)			
		((eq? target 'm3) -3)
		((eq? target 'M3) 4)	
		((or (eq? target 'p4) (eq? target 'P4)) -1)	
		((or (eq? target 't) (eq? target 'T)) 6)		
		((or (eq? target 'p5) (eq? target 'P5)) 1)
		((eq? target 'm6) -4)			
		((eq? target 'M6) 3)		
		((eq? target 'm7) -2)	
		((eq? target 'M7) 5)		
		(else #f)
	)		
)



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;Functions;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Checks if a string is a lilypond note compatible with (d-ChangeChordNotes)
;(define (ANS::IsLily?)
;	
;)

(define (ANS::Ly2Ans lilynote) ;wants symbol, returns number
	(hashq-ref ANS::NoteTableR lilynote))

(define (ANS::Ans2Ly ansNote) ;wants number, returns symbol
	(hashq-ref ANS::NoteTable ansNote))

; The main function to get notes from Denemo
; Opposite is ANS::ChangeChordNotes
; For singles and chords and rests. Returns a list of ANS-numbers as chord.
(define (ANS::GetChordNotes)
	(if (Note?)
		(map (lambda (value) (ANS::Ly2Ans (string->symbol value))) (string-tokenize (d-GetNotes)))
		(if (Rest?) ; not a note
			(list +inf.0)
			#f)))

; Change chord/note to another chord/note
; The main function to get ANS back to Denemo via (d-ChangeChordNotes)
; Opposite is ANS::GetChordNotes
; Wants a ANS-number or list of ANS numbers.
(define (ANS::ChangeChordNotes ansNotes)
	(define newList '())
	(if (list? ansNotes) ; check if it was a single note, in this case make a list.
		#t
		(set! ansNotes (list ansNotes)))
	(set! newList (map (lambda (value) (symbol->string (ANS::Ans2Ly value))) ansNotes))
	(d-ChangeChordNotes (string-join newList))) ; d-ChangeChordNotes wants a long string of notes with space between.


;Insert A note/chord on Denemos cursor position 
; wants a single or a list of ANS numbers (chord).
; Optional duration and number of dots. Denemo Syntax. returns #t or #f. 
(define* (ANS::InsertNotes ansNotes #:optional (dots #f) (duration #f) )
	;TODO: Check if these are valid notes.
	(d-InsertA) ; TODO: This is a hack. There is no way to directly insert notes with lilypond syntax
	(d-MoveCursorLeft)
	(ANS::ChangeChordNotes ansNotes)
	(if duration  ;If user gave duration parameter. Does not test if the duration is a valid number
			(eval-string (string-append "(d-Change" (number->string duration) ")"))) ; TODO: eval string should be gone. And it does not support breve and longa!
	(if (and dots (not (= dots 0))) ;If the user gave 0 as durations ignore that as well
			(let loop ((count 0)) 
				(d-AddDot)
				(if (< count (- dots 1))
				(loop (+ 1 count)))))
	(d-MoveCursorRight))


; Extract the note from an ANS-number, without any octave but with the tailing zero. Return as number.
; This means we double-use the lowest octave as abstract version.
; Dividing through the octave, 350, results in the number of the octave and the note as remainder.
(define (ANS::GetNote ansNote) 
		(remainder ansNote 350))

;Extract the octave as integer, where c,,, is in the 0 octave. 
(define (ANS::GetOctave ansNote) 
	(quotient ansNote 350))

; Return the natural, "white key" version of an ansNote.
(define (ANS::GetWhiteKey ansNote) 
	; /50 without rest to get a multiplier that will...
 	; *50 return the "...eses" version which is a multiple of 50. 
 	; +20 from "...eses" to plain.
 	(+ 20 (* 50 (quotient ansNote 50))))

;Alteration adds a sharp, flat or nothing to a ans-note. Returns an ANS
;number. Wants an ans number and a procedure that will return either 0, 1 or -1. 
(define (ANS::Alteration ansNote modificator)
	(case modificator
	  ((0)		ansNote) ; natural, no change
	  ((1)		(+ ansNote  10)) ;sharp
	  ((-1)		(- ansNote  10)) ;flat
	  (else   #f))) ; someone might introduce some insane feature in the future where you can add doublecrosses or similar to a keysig. Or maybe there is even a real usage for micotonals like turkish maqam.
	 


;IntervalCalc wants an ANS note as root and an interval like "m2", "M6" or "p5" returns an ANS value.
;Op is needed to calc up or down. 1 is up, -1 is down.
(define (ANS::IntervalCalcPrototype op ansNote interval)
 (define targ (ANS::IntervalGetSteps interval))
 (define root (hashq-ref ANS::PillarOfFifthIndex (ANS::GetNote ansNote)))
 (list-ref ANS::PillarOfFifth (+ root (* op targ))))  


;Since IntervalCalcPrototype just returns a note name without octave we must check if the new note with the old octave is really above the old, if not shift it.
(define (ANS::IntervalCalcUp ansNote interval)
	(define result	(ANS::IntervalCalcPrototype 1 ansNote interval))
	(define octave (* 350 (ANS::GetOctave ansNote))) ; gets us an octave counter. * 350 to make it addable.
	(if (>= result (ANS::GetNote ansNote)) ; test if the calulated interval, just one digit until now, will be in the same octave which means its note-value itself is higher or equal (in case of p1) compared to the root. Or it seems to be lower, in this case we need to add an octave because we really want it higher
		 (+ octave result) ;its still in the same octave, just recalculate
		 (+ octave 350 result))) ;+350 to go one octave up


(define (ANS::IntervalCalcDown ansNote interval)
	(define result (ANS::IntervalCalcPrototype -1 ansNote interval))
	(define octave (* 350 (ANS::GetOctave ansNote)))	
	(if (<= result (ANS::GetNote ansNote)) 
		 (+ octave result) 
		 (+ octave -350 result))) ;-350 to go one octave down

(define (ANS::CalculateRealOctaveUp ansNote) 
	(+ ansNote 350))

(define (ANS::CalculateRealOctaveDown ansNote) 
	(- ansNote 350))


;GetDiatonic. Looks ups the prevailing keysignature and returns the correct diatonic value for a given note.
; PrevailingKeysig is either -1 (flat), 0 (natural) or 1 (sharp)
(define (ANS::GetDiatonic ansNote)
	(define keysiglist (string-tokenize (d-GetPrevailingKeysig))) ; A list of strings! We need numbers, later
	(define whitekey (ANS::GetWhiteKey ansNote))
	(define getkeysigfor "0")
	
	(set! getkeysigfor 	; Is used by the new note to sharpen 1, flatten -1, or stay natural 0. 
	   (cond		  	; each list-ref position for keysiglist is one diatonic note position from c to b.
		((= 20 (ANS::GetNote whitekey)) (list-ref keysiglist 0)) ; Test which note the white-key version is and send the corresponding sharp/flat/natural modificator to ANS::Alteration later.
		((= 70 (ANS::GetNote whitekey)) (list-ref keysiglist 1)) ; Only one can be true because we test one note alone.
		((= 120 (ANS::GetNote whitekey)) (list-ref keysiglist 2))
		((= 170 (ANS::GetNote whitekey)) (list-ref keysiglist 3))
		((= 220 (ANS::GetNote whitekey)) (list-ref keysiglist 4))
		((= 270 (ANS::GetNote whitekey)) (list-ref keysiglist 5))
		((= 320 (ANS::GetNote whitekey)) (list-ref keysiglist 6))
	     )) 
       (ANS::Alteration whitekey (string->number getkeysigfor)))  ; keysiglist-members are strings so we need to convert first


; Wrapper functions to make Diatonic Steps easier.
(define (ANS::CalculateDiatonicStepUp ansNote) (ANS::GetDiatonic (+ ansNote 50))) ; feed the Keysig-reference with the target note (+50), not the origin one.
(define (ANS::CalculateDiatonicStepDown ansNote) (ANS::GetDiatonic (- ansNote 50)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;Analaysis;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Convert two ANS notes to one ANS interval
;Return pair in pair: (intervall (lower . higher))
(define	(ANS::GetIntervall ansNoteOne ansNoteTwo)
	(define higher ansNoteOne)
	(define lower ansNoteTwo)
	(if (<= ansNoteOne ansNoteTwo) ; bring the notes in right order. We want to calculate from top to bottom.
		(begin 	(set! lower ansNoteOne)
				(set! higher ansNoteTwo)))		

	;Extract the tone, without octave and feed it to the hash to get the notes position in the pillar of 5th.
	(cons
		(- (hashq-ref ANS::PillarOfFifthIndex (ANS::GetNote higher)) (hashq-ref ANS::PillarOfFifthIndex (ANS::GetNote lower)))
		(cons lower higher)))


;GetIntervall for lists. 
;Converts a list of pairs(lower note and higher ANS note) to a list of interval numbers (ans syntax. steps in the pillar of 5th)
(define (ANS::CreateIntervalsFromPairs listy) ;Wants a list of pairs.
	(define (GetIntv pair)
		(ANS::GetIntervall (car pair) (cdr pair)))
	(map GetIntv listy))

; forbidden compares two list (of intervals. ANS syntax) and checks if a sequence of intervals is the same and if this sequcence is forbidden
;; Used to detect often forbidden parallels of 5th or 8th or 1th etc. 
;; Lists should be the same length (means the same amount of intervals, which is the case when both lists are generated from chords with the same number of notes)
;; Repetitions and Octave shifts return as #f. (not (equal?...)) tests for repeats, ANS::GetNote equalizes octaves
;; Expects pair in pair: (intervall (lower . higher)) from ANS::GetIntervall
(define (ANS::Forbidden? list1 list2 forbidden)
     (define (test? one two) 
		(and (equal? (car one) (car two)) (not (equal? (ANS::GetNote (car (cdr one))) (ANS::GetNote (car (cdr two))) )) (if (member (car one) forbidden) #t #f)))
      (if (member #t (map test? list1 list2))
		  #t
		  #f))
       

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;Random Note Generation;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;TODO: no chords possible yet. It shouldn't matter if you are dealing with chords or single notes.
               
; Generates a random note within a given range. The range includes both values.
(define (ANS::random from to)
	(let (
		  (from (/ from 10)) ;drop microtones, just use the chromatic/enharmonic material
		  (to (/ to 10))
		  (rand 0)
		 )
	(set! to (+ 1 (- to from))) ; (- to from ) means only use the relative range, not absolute values . +1 to include the last, given value. 
	(set! rand  (+ from (random to)) ) ; get a random value in the range and then shift the relative range to start from "from"
	(* rand 10))) ; convert to octave scale again and return	

;Random note generator, respects the keysignature. Insert an optional range, default is all 56 diatonic notes.
(define* (ANS::RandomDiatonic #:optional (from 0) (to 3150))
	(ANS::GetDiatonic (ANS::random from to))	
)

;Random note generator, one of each possible chromatic notes or optional range. Same probability for natural, flat or sharp.
(define* (ANS::RandomChromatic #:optional (from 0) (to 3140))
	(define rand (- (random 3) 1))	; -1, 0 or 1
	(ANS::Alteration (ANS::RandomDiatonic from to) rand) 
)  


;Takes a list of notes, shuffle the members and inserts them as new notes.
(define (ANS::InsertListRandomly ansList)
	(define shuffledlist (Merge-shuffle-list ansList))
	(for-each ANS::InsertNotes shuffledlist)
)

;Takes a list of notes and randomly pick one to insert. The member
;remains in the original list but the function returns a new list without the
;inserted value. 
(define (ANS::InsertMemberRandomly ansList)
	(define rnd (random (length ansList) ))
	(define ANSListcopy (list-copy ansList))
	(ANS::InsertNotes (list (list-ref ansList rnd) ))
	(if (= rnd 0) ;delete1! cannot delete first item
	   (list-tail ANSListcopy 1)
	   (delete1! (list-ref ANSListcopy rnd) ANSListcopy)	
	)
)

;; Example to enter random triads. Uses nearly the complete featureset of ANS as of today. Creating random notes in a range, making it diatonic and then calculate intervals to add up and down and finally placing all as real Denemo notation, as chord at once.
;(define zz (ANS::RandomDiatonic 420 520 ))     (ANS::InsertNotes  (list zz (ANS::IntervalCalcUp zz 'p5) (ANS::GetDiatonic (ANS::IntervalCalcUp zz 'M3)) ) )
