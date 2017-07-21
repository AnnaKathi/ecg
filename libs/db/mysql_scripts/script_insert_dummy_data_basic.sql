# //Dummy-Daten in alle Datenbank eintragen: Grunddefinitionen
#
# //-- Diseases
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Koronare Herzkrankheit');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Angina Pectoris');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzklappendefekt');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzinfarkt');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Herzschwäche');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Myokarditis');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Tachykardie');
INSERT INTO `ecg`.`diseases` (`Name`) VALUES ('Bradykardie');

# //-- Orte
INSERT INTO `ecg`.`places` (`Name`) VALUES ('Verein - Umkleide');

# //-- Researchers
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Anna Stratmann');
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Ralph Breithaupt');
INSERT INTO `ecg`.`researchers` (`Name`) VALUES ('Gerd Nolden');

# //-- Lagen
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('liegend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('sitzend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('stehend');
INSERT INTO `ecg`.`postures` (`Name`) VALUES ('gehend');

# //-- States
INSERT INTO `ecg`.`states` (`Name`) VALUES ('in Ruhe');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('in Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach leichter Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach mäßiger Bewegung');
INSERT INTO `ecg`.`states` (`Name`) VALUES ('nach viel Bewegung');

# //-- Positionens
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Brust normal');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Brust eng');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Handrücken');
INSERT INTO `ecg`.`positions` (`Name`) VALUES ('Rücken');

# //-- Algorithmen
INSERT INTO `ecg`.`algrpeaks` (`Name`) VALUES ('rpeaksAnna');
INSERT INTO `ecg`.`algrpeaks` (`Name`) VALUES ('rpeaksChoi');

INSERT INTO `ecg`.`algfeatures` (`Name`) VALUES ('featChoi');
INSERT INTO `ecg`.`algfeatures` (`Name`) VALUES ('featRandomPoints');
INSERT INTO `ecg`.`algfeatures` (`Name`) VALUES ('featWaili3QRS');

INSERT INTO `ecg`.`algpreproc` (`Name`) VALUES ('preNone');
INSERT INTO `ecg`.`algpreproc` (`Name`) VALUES ('preAC');

