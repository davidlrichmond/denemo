;;; Warning!!! This file is derived from those in actions/menus/... do not edit here
;;HelpAllFeatures
(d-NewWindow)
(if  (d-OpenExample "AllFeaturesExplained.denemo")
	(d-PrintView)
	(begin
		(d-WarningDialog "System Example file not found. Check Installation")
		(d-Close)))