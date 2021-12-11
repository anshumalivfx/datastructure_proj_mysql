-- phpMyAdmin SQL Dump
-- version 5.0.4
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: Dec 11, 2021 at 10:57 PM
-- Server version: 10.4.17-MariaDB
-- PHP Version: 8.0.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `librarymanagement`
--

-- --------------------------------------------------------

--
-- Table structure for table `books`
--

CREATE TABLE `books` (
  `title` varchar(100) NOT NULL,
  `author` varchar(100) NOT NULL,
  `publisher` varchar(100) NOT NULL,
  `year` varchar(4) NOT NULL,
  `isbn` varchar(40) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `books`
--

INSERT INTO `books` (`title`, `author`, `publisher`, `year`, `isbn`) VALUES
('Ayushi', 'Ayushi Bawari', 'JIIT', '2021', 'NEWBOOK'),
('Ayushi', 'Ayushi bawari', 'askjda', '2021', 'asndjabn'),
('Ayushi', 'Ayushi bawari', 'askjda', '2021', 'asndjabn'),
('Ishika', 'Ishika Dhanai', 'Pure', '2021', 'askda'),
('Ayushi', 'Ayushi bawari', 'askjda', '2021', 'asndjabn'),
('Ayushi', 'Ayushi bawari', 'askjda', '2021', 'asndjabn'),
('Ayushi', 'Ayushi Bawari', 'JIIT', '2021', 'NEWBOOK');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
