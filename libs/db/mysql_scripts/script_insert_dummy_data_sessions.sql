# //Dummy-Daten in alle Datenbank eintragen: Session-Daten
#
# //-- Subjects, 1=weiblich, 0=männlich
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Sex`, `Age`, `Height`, `Weight`) VALUES ('Anna', 'Stratmann', 1, 35, 175, 73);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Sex`, `Age`, `Height`, `Weight`) VALUES ('Manfred', 'Umlauff', 0, 63, 176, 72);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Sex`, `Age`, `Height`, `Weight`) VALUES ('Manuela', 'Stratmann', 1, 57, 170, 65);
INSERT INTO `ecg`.`subjects` (`Firstname`, `Lastname`, `Sex`, `Age`, `Height`, `Weight`) VALUES ('Martin', 'Stratmann', 0, 59, 180, 82);

# //-- Sub-Diseases, Diseases 1-8, Subjects 1-4
# //Anna ist gesund, bei Manfred, Martin und Manuela Krankheiten simulieren
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 1);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 5);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (2, 7);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (3, 2);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 3);
INSERT INTO `ecg`.`subdiseases` (`Subjects_ID`, `Diseases_ID`) VALUES (4, 5);

# //-- Sessions, drei Sessions simulieren

# //-- Session-Researchers

# //-- EcgData, Manfred liegend2

# //-- Erkennungswerte

