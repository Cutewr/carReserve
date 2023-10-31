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
-- Table structure for table `ParkingFee`
--

DROP TABLE IF EXISTS `ParkingFee`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `ParkingFee` (
  `FeeID` int NOT NULL AUTO_INCREMENT,
  `VehicleID` varchar(20) DEFAULT NULL,
  `EntryTime` datetime DEFAULT NULL,
  `ExitTime` datetime DEFAULT NULL,
  `FeeAmount` int DEFAULT NULL,
  `PayWay` enum('cash','wechat','alipay') DEFAULT NULL,
  `VehicleType` enum('Internal','Visitor','Registered') NOT NULL,
  PRIMARY KEY (`FeeID`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `ParkingFee`
--

LOCK TABLES `ParkingFee` WRITE;
/*!40000 ALTER TABLE `ParkingFee` DISABLE KEYS */;
INSERT INTO `ParkingFee` VALUES (1,'鄂A1GQ82','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(2,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(3,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(4,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(5,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'cash','Internal'),(6,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'cash','Internal'),(7,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(8,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(9,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'cash','Internal'),(10,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Internal'),(11,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'wechat','Internal'),(12,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'wechat','Internal'),(13,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'cash','Internal'),(14,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(15,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(16,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(17,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(18,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Internal'),(19,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'wechat','Internal'),(20,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',0,'alipay','Visitor'),(21,'鄂A12345','2023-09-03 07:10:00','2023-09-03 10:53:00',24,'alipay','Visitor'),(22,'鄂A12345','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'alipay','Visitor'),(23,'鄂A12343','2023-09-04 07:10:00','2023-09-04 10:53:00',0,'wechat','Internal'),(24,'鄂A12343','2023-09-04 07:10:00','2023-09-04 10:53:00',0,'alipay','Internal'),(25,'鄂A45678','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'alipay','Visitor'),(26,'鄂A45678','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'wechat','Visitor'),(27,'鄂A45678','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'alipay','Visitor'),(28,'鄂A45678','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'wechat','Visitor'),(29,'鄂A45678','2023-09-04 07:10:00','2023-09-04 10:53:00',24,'cash','Visitor'),(30,'鄂A1234','2023-09-09 07:10:00','2023-09-09 10:53:00',24,'alipay','Visitor'),(31,'鄂A1234','2023-09-09 07:10:00','2023-09-09 10:53:00',24,'alipay','Visitor'),(32,'鄂A5678','2023-09-09 07:10:00','2023-09-09 10:53:00',0,'wechat','Visitor'),(33,'鄂A5678','2023-09-09 07:10:00','2023-09-09 10:53:00',0,'alipay','Internal'),(34,'鄂A1234','2023-09-09 07:10:00','2023-09-09 10:53:00',24,'cash','Visitor');
/*!40000 ALTER TABLE `ParkingFee` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2023-09-09 13:37:26
