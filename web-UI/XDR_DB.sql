-- phpMyAdmin SQL Dump
-- version 4.7.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Creato il: Gen 11, 2018 alle 09:57
-- Versione del server: 5.7.17
-- Versione PHP: 7.1.7

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;

--
-- Database: `XDR_DB`
--

-- --------------------------------------------------------

--
-- Struttura della tabella `crash`
--

CREATE TABLE `xdr_crash` (
  `id` int(11) NOT NULL,
  `crashtime` datetime NOT NULL,
  `intensity` int(11) NOT NULL,
  `stationary` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `crash`
--

INSERT INTO `xdr_crash` (`id`, `crashtime`, `intensity`, `stationary`) VALUES
(1, '2018-01-07 07:00:00', 2, 0),
(2, '2018-01-02 02:00:00', 2, 0),
(3, '2018-01-07 01:00:00', 2, 1),
(3, '2018-01-07 03:00:00', 2, 1),
(3, '2018-01-07 04:00:00', 4, 1),
(3, '2018-01-07 05:00:00', 3, 1),
(3, '2018-01-08 02:03:00', 3, 0);

-- --------------------------------------------------------

--
-- Struttura della tabella `evaluation`
--

CREATE TABLE `xdr_evaluation` (
  `id` int(11) NOT NULL,
  `pointstotal` int(11) NOT NULL DEFAULT '0',
  `pointsacceleration` int(11) NOT NULL DEFAULT '0',
  `pointsbraking` int(11) NOT NULL DEFAULT '0',
  `pointssteering` int(11) NOT NULL DEFAULT '0',
  `pointsspeed` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `evaluation`
--

INSERT INTO `xdr_evaluation` (`id`, `pointstotal`, `pointsacceleration`, `pointsbraking`, `pointssteering`, `pointsspeed`) VALUES
(1, 50, 49, 51, 48, 52),
(2, 49, 51, 49, 52, 48),
(3, 40, 50, 40, 55, 80);

-- --------------------------------------------------------

--
-- Struttura della tabella `resume`
--

CREATE TABLE `xdr_resume` (
  `email` varchar(254) NOT NULL,
  `pointstotal` int(11) NOT NULL DEFAULT '0',
  `pointsacceleration` int(11) NOT NULL DEFAULT '0',
  `pointsbraking` int(11) NOT NULL DEFAULT '0',
  `pointssteering` int(11) NOT NULL DEFAULT '0',
  `pointsspeed` int(11) NOT NULL DEFAULT '0',
  `drivenhours` float NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `resume`
--

INSERT INTO `xdr_resume` (`email`, `pointstotal`, `pointsacceleration`, `pointsbraking`, `pointssteering`, `pointsspeed`, `drivenhours`) VALUES
('gabriele_serra@hotmail.it', 61, 41, 39, 82, 82, 3.5);

-- --------------------------------------------------------

--
-- Struttura della tabella `stat`
--

CREATE TABLE `xdr_stat` (
  `id` int(11) NOT NULL,
  `numberacc` int(11) NOT NULL DEFAULT '0',
  `worstacc` int(11) NOT NULL DEFAULT '0',
  `numberbra` int(11) NOT NULL DEFAULT '0',
  `worstbra` int(11) NOT NULL DEFAULT '0',
  `numbercur` int(11) NOT NULL DEFAULT '0',
  `worstcur` int(11) NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `stat`
--

INSERT INTO `xdr_stat` (`id`, `numberacc`, `worstacc`, `numberbra`, `worstbra`, `numbercur`) VALUES
(1, 1, 2, 1, 5, 3),
(2, 0, 0, 1, 4, 0),
(3, 2, 5, 3, 1, 5);

-- --------------------------------------------------------

--
-- Struttura della tabella `trip`
--

CREATE TABLE `xdr_trip` (
  `id` int(11) NOT NULL,
  `email` varchar(254) NOT NULL,
  `meters` int(11) NOT NULL DEFAULT '0',
  `starttime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `secondslength` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `trip`
--

INSERT INTO `xdr_trip` (`id`, `email`, `meters`, `starttime`, `secondslength`) VALUES
(1, 'gabriele_serra@hotmail.it', 50, '2018-01-07 06:30:00', 120),
(2, 'gabriele_serra@hotmail.it', 100, '2018-01-07 12:32:00', 90),
(3, 'gabriele_serra@hotmail.it', 90, '2018-01-05 04:15:00', 180);

-- --------------------------------------------------------

--
-- Struttura della tabella `user`
--

CREATE TABLE `xdr_user` (
  `email` varchar(254) NOT NULL,
  `username` varchar(255) NOT NULL,
  `password` varchar(32) NOT NULL,
  `name` varchar(255) NOT NULL,
  `surname` varchar(255) NOT NULL,
  `bio` varchar(280) NOT NULL DEFAULT 'A long time ago in a galaxy far far away',
  `avatar` varchar(255) NOT NULL DEFAULT 'avatar-default.png',
  `cover` varchar(255) NOT NULL DEFAULT 'cover-default.png'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dump dei dati per la tabella `user`
--

INSERT INTO `xdr_user` (`email`, `username`, `password`, `name`, `surname`, `bio`, `avatar`, `cover`) VALUES
('gabriele_serra@hotmail.it', 'gabriserra', 'dc647eb65e6711e155375218212b3964', 'Gabriele', 'Serra', 'A long time ago in a galaxy far far away', 'avatar-gabriserra.png', 'cover-gabriserra.png');

--
-- Indici per le tabelle scaricate
--

--
-- Indici per le tabelle `crash`
--
ALTER TABLE `xdr_crash`
  ADD PRIMARY KEY (`id`,`crashtime`);

--
-- Indici per le tabelle `evaluation`
--
ALTER TABLE `xdr_evaluation`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `resume`
--
ALTER TABLE `xdr_resume`
  ADD PRIMARY KEY (`email`);

--
-- Indici per le tabelle `stat`
--
ALTER TABLE `xdr_stat`
  ADD PRIMARY KEY (`id`);

--
-- Indici per le tabelle `trip`
--
ALTER TABLE `xdr_trip`
  ADD PRIMARY KEY (`id`),
  ADD KEY `email` (`email`);

--
-- Indici per le tabelle `user`
--
ALTER TABLE `xdr_user`
  ADD PRIMARY KEY (`email`),
  ADD UNIQUE KEY `username` (`username`);

--
-- AUTO_INCREMENT per le tabelle scaricate
--

--
-- AUTO_INCREMENT per la tabella `trip`
--
ALTER TABLE `xdr_trip`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;
--
-- Limiti per le tabelle scaricate
--

--
-- Limiti per la tabella `crash`
--
ALTER TABLE `xdr_crash`
  ADD CONSTRAINT `xdr_crash_ibfk_1` FOREIGN KEY (`id`) REFERENCES `xdr_trip` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `evaluation`
--
ALTER TABLE `xdr_evaluation`
  ADD CONSTRAINT `xdr_evaluation_ibfk_1` FOREIGN KEY (`id`) REFERENCES `xdr_trip` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `resume`
--
ALTER TABLE `xdr_resume`
  ADD CONSTRAINT `xdr_resume_ibfk_1` FOREIGN KEY (`email`) REFERENCES `xdr_user` (`email`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `stat`
--
ALTER TABLE `xdr_stat`
  ADD CONSTRAINT `xdr_stat_ibfk_1` FOREIGN KEY (`id`) REFERENCES `xdr_trip` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Limiti per la tabella `trip`
--
ALTER TABLE `xdr_trip`
  ADD CONSTRAINT `xdr_trip_ibfk_1` FOREIGN KEY (`email`) REFERENCES `xdr_user` (`email`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
