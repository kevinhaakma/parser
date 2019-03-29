-- phpMyAdmin SQL Dump
-- version 4.8.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Gegenereerd op: 29 mrt 2019 om 11:50
-- Serverversie: 5.5.60-MariaDB
-- PHP-versie: 5.6.30

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `chatbot`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Actors`
--

CREATE TABLE `Actors` (
  `ActorID` int(11) NOT NULL,
  `Actor` varchar(120) NOT NULL,
  `Gender` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Countries`
--

CREATE TABLE `Countries` (
  `CountryID` int(11) NOT NULL,
  `Country` varchar(120) NOT NULL,
  `MovieID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Directed`
--

CREATE TABLE `Directed` (
  `MovieID` int(11) NOT NULL,
  `DirectorID` int(11) NOT NULL,
  `Role` varchar(120) NOT NULL,
  `RoleID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Directors`
--

CREATE TABLE `Directors` (
  `DirectorID` int(11) NOT NULL,
  `Name` varchar(120) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Genres`
--

CREATE TABLE `Genres` (
  `GenreID` int(11) NOT NULL,
  `Genre` varchar(120) NOT NULL,
  `MovieID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Movies`
--

CREATE TABLE `Movies` (
  `MovieID` int(11) NOT NULL,
  `Movie` varchar(120) NOT NULL,
  `Year` int(4) DEFAULT '9999',
  `Studio` varchar(120) NOT NULL,
  `SerieName` varchar(120) NOT NULL,
  `SerieSeason` int(2) NOT NULL,
  `EpisodeNumber` int(2) NOT NULL,
  `EndSeason` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Ratings`
--

CREATE TABLE `Ratings` (
  `RatingID` int(11) NOT NULL,
  `Distribution` char(10) NOT NULL,
  `Votes` int(11) NOT NULL,
  `Rank` double NOT NULL,
  `MovieID` int(11) NOT NULL,
  `Year` int(4) DEFAULT '9999'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Roles`
--

CREATE TABLE `Roles` (
  `RoleID` int(11) NOT NULL,
  `ActorID` int(11) NOT NULL,
  `MovieID` int(11) NOT NULL,
  `Role` varchar(120) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `Soundtracks`
--

CREATE TABLE `Soundtracks` (
  `SoundtrackID` int(11) NOT NULL,
  `Soundtrack` varchar(120) NOT NULL,
  `Composer` varchar(120) NOT NULL,
  `Performer` varchar(120) DEFAULT 'null',
  `Year` int(4) NOT NULL DEFAULT '9999',
  `MovieID` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Indexen voor geëxporteerde tabellen
--

--
-- Indexen voor tabel `Actors`
--
ALTER TABLE `Actors`
  ADD PRIMARY KEY (`ActorID`);

--
-- Indexen voor tabel `Countries`
--
ALTER TABLE `Countries`
  ADD PRIMARY KEY (`CountryID`),
  ADD KEY `movie` (`MovieID`);

--
-- Indexen voor tabel `Directed`
--
ALTER TABLE `Directed`
  ADD PRIMARY KEY (`RoleID`),
  ADD KEY `director` (`DirectorID`),
  ADD KEY `movie` (`MovieID`);

--
-- Indexen voor tabel `Directors`
--
ALTER TABLE `Directors`
  ADD PRIMARY KEY (`DirectorID`);

--
-- Indexen voor tabel `Genres`
--
ALTER TABLE `Genres`
  ADD PRIMARY KEY (`GenreID`),
  ADD KEY `movie` (`MovieID`);

--
-- Indexen voor tabel `Movies`
--
ALTER TABLE `Movies`
  ADD PRIMARY KEY (`MovieID`);

--
-- Indexen voor tabel `Ratings`
--
ALTER TABLE `Ratings`
  ADD PRIMARY KEY (`RatingID`),
  ADD KEY `movie` (`MovieID`);

--
-- Indexen voor tabel `Roles`
--
ALTER TABLE `Roles`
  ADD PRIMARY KEY (`RoleID`),
  ADD KEY `actor` (`ActorID`),
  ADD KEY `movie` (`MovieID`);

--
-- Indexen voor tabel `Soundtracks`
--
ALTER TABLE `Soundtracks`
  ADD PRIMARY KEY (`SoundtrackID`),
  ADD KEY `movie` (`MovieID`);

--
-- AUTO_INCREMENT voor geëxporteerde tabellen
--

--
-- AUTO_INCREMENT voor een tabel `Actors`
--
ALTER TABLE `Actors`
  MODIFY `ActorID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Countries`
--
ALTER TABLE `Countries`
  MODIFY `CountryID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Directed`
--
ALTER TABLE `Directed`
  MODIFY `RoleID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Directors`
--
ALTER TABLE `Directors`
  MODIFY `DirectorID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Genres`
--
ALTER TABLE `Genres`
  MODIFY `GenreID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Movies`
--
ALTER TABLE `Movies`
  MODIFY `MovieID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Ratings`
--
ALTER TABLE `Ratings`
  MODIFY `RatingID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Roles`
--
ALTER TABLE `Roles`
  MODIFY `RoleID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT voor een tabel `Soundtracks`
--
ALTER TABLE `Soundtracks`
  MODIFY `SoundtrackID` int(11) NOT NULL AUTO_INCREMENT;

--
-- Beperkingen voor geëxporteerde tabellen
--

--
-- Beperkingen voor tabel `Actors`
--
ALTER TABLE `Actors`
  ADD CONSTRAINT `Actors_ibfk_1` FOREIGN KEY (`ActorID`) REFERENCES `Roles` (`ActorID`);

--
-- Beperkingen voor tabel `Countries`
--
ALTER TABLE `Countries`
  ADD CONSTRAINT `Countries_ibfk_1` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`);

--
-- Beperkingen voor tabel `Directed`
--
ALTER TABLE `Directed`
  ADD CONSTRAINT `Directed_ibfk_2` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`),
  ADD CONSTRAINT `Directed_ibfk_1` FOREIGN KEY (`DirectorID`) REFERENCES `Directors` (`DirectorID`);

--
-- Beperkingen voor tabel `Directors`
--
ALTER TABLE `Directors`
  ADD CONSTRAINT `Directors_ibfk_1` FOREIGN KEY (`DirectorID`) REFERENCES `Directed` (`DirectorID`);

--
-- Beperkingen voor tabel `Genres`
--
ALTER TABLE `Genres`
  ADD CONSTRAINT `Genres_ibfk_1` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`);

--
-- Beperkingen voor tabel `Ratings`
--
ALTER TABLE `Ratings`
  ADD CONSTRAINT `Ratings_ibfk_1` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`);

--
-- Beperkingen voor tabel `Roles`
--
ALTER TABLE `Roles`
  ADD CONSTRAINT `Roles_ibfk_2` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`),
  ADD CONSTRAINT `Roles_ibfk_1` FOREIGN KEY (`ActorID`) REFERENCES `Actors` (`ActorID`);

--
-- Beperkingen voor tabel `Soundtracks`
--
ALTER TABLE `Soundtracks`
  ADD CONSTRAINT `Soundtracks_ibfk_1` FOREIGN KEY (`MovieID`) REFERENCES `Movies` (`MovieID`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
