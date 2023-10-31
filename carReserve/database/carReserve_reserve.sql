-- MySQL dump 10.13  Distrib 8.0.34, for Linux (x86_64)
--
-- Host: localhost    Database: carReserve
-- ------------------------------------------------------
-- Server version	8.0.34-0ubuntu0.22.04.1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `reserve`
--

DROP TABLE IF EXISTS `reserve`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `reserve` (
  `reserve_id` int NOT NULL AUTO_INCREMENT,
  `staff_no` varchar(10) NOT NULL,
  `date` datetime NOT NULL,
  `way` enum('walk','drive') NOT NULL DEFAULT 'walk',
  `cause` enum('official','personal') NOT NULL DEFAULT 'official',
  `vehicle_id` varchar(20) DEFAULT NULL,
  `visitor_id` varchar(20) DEFAULT NULL,
  PRIMARY KEY (`reserve_id`)
) ENGINE=InnoDB AUTO_INCREMENT=12 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `reserve`
--

LOCK TABLES `reserve` WRITE;
/*!40000 ALTER TABLE `reserve` DISABLE KEYS */;
INSERT INTO `reserve` VALUES (1,'12345','2023-08-22 00:00:00','drive','personal','鄂A123456','420100200301020023'),(2,'12345','2023-08-23 00:00:00','drive','official','鄂A1GQ82','4121002003010500012'),(3,'12345','2023-08-24 00:00:00','drive','official','鄂A123456','412100200301030029'),(4,'12345','2023-08-12 00:00:00','drive','personal','鄂A12345','412100200301030029'),(5,'12346','2023-08-12 00:00:00','drive','personal','鄂A2345','420100200102010021'),(6,'12345','2023-09-03 00:00:00','drive','official','鄂A12345','341003200301060029'),(7,'12345','2023-09-04 00:00:00','drive','official','鄂A12345','341003200301060029'),(8,'12345','2023-09-04 00:00:00','drive','official','鄂A12354','341003200301060029'),(9,'12345','2023-09-04 00:00:00','drive','official','鄂A12354','341003200301060029'),(10,'12345','2023-09-04 00:00:00','drive','official','鄂A45678','341003200301060023'),(11,'12345','2023-09-09 00:00:00','drive','official','鄂A1234','341003200301060024');
/*!40000 ALTER TABLE `reserve` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-09-09 13:37:27
