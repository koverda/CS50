-- MySQL dump 10.13  Distrib 5.5.41, for debian-linux-gnu (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.41-0ubuntu0.14.04.1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `userid` int(10) NOT NULL,
  `buysell` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(20) NOT NULL,
  `price` float NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (1,6,'SELL','FB',130,75.78,'2015-01-28 02:01:23'),(2,6,'BUY','FB',10,75.78,'2015-01-28 02:04:55'),(3,6,'BUY','AAPL',10,109.14,'2015-01-28 02:05:04'),(4,6,'BUY','IBM',10,153.67,'2015-01-28 02:05:11'),(5,6,'BUY','F',10,14.85,'2015-01-28 02:43:30'),(6,6,'SELL','F',10,14.85,'2015-01-28 02:50:56'),(7,6,'SELL','AAPL',10,109.14,'2015-01-28 02:51:51'),(8,6,'SELL','FB',10,75.78,'2015-01-28 02:54:16'),(9,6,'SELL','IBM',10,153.67,'2015-01-28 02:56:25'),(10,6,'BUY','F',1,14.85,'2015-01-28 03:01:08'),(11,6,'BUY','FB',1,75.78,'2015-01-28 03:01:14'),(12,6,'BUY','YHOO',1,47.99,'2015-01-28 03:01:19'),(13,6,'BUY','IBM',1,153.67,'2015-01-28 03:01:28'),(14,6,'BUY','Z',1,102.42,'2015-01-28 03:01:34'),(15,6,'SELL','F',1,14.85,'2015-01-28 03:02:27'),(16,6,'SELL','FB',1,75.78,'2015-01-28 03:08:08'),(17,6,'SELL','IBM',1,153.67,'2015-01-28 03:10:36'),(18,6,'BUY','Z',1,102.42,'2015-01-28 03:11:52'),(19,6,'BUY','FB',10,75.78,'2015-01-28 03:12:39'),(20,6,'BUY','FB',10,75.78,'2015-01-28 03:12:58'),(21,8,'BUY','FB',1,75.78,'2015-01-28 03:30:36');
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `id` int(10) NOT NULL,
  `symbol` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(10) NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES (6,'FB',20),(6,'YHOO',1),(6,'Z',2),(8,'FB',1);
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` float NOT NULL DEFAULT '10000',
  `email` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'belindazeng','$1$50$oxJEDBo9KDStnrhtnSzir0',10000,''),(2,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000,''),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000,''),(4,'malan','$1$50$lJS9HiGK6sphej8c4bnbX.',10000,''),(5,'rob','$1$HA$l5llES7AEaz8ndmSo5Ig41',10000,''),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',8231.57,'koverd.a@gmail.com'),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000,''),(8,'peet','$1$idifq84x$zOHkGw8/akH5di/Z5mYxP/',9924.22,'koverda@gmail.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2015-01-27 19:31:29
