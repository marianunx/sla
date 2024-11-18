-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 18/11/2024 às 15:11
-- Versão do servidor: 10.4.32-MariaDB
-- Versão do PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `confeitaria`
--

-- --------------------------------------------------------

--
-- Estrutura para tabela `produtos_confeitaria`
--

CREATE TABLE `produtos_confeitaria` (
  `id` int(11) NOT NULL,
  `nome` varchar(255) NOT NULL,
  `preco_por_grama` decimal(10,2) NOT NULL,
  `peso` decimal(10,2) NOT NULL,
  `preco_final` decimal(10,2) GENERATED ALWAYS AS (`preco_por_grama` * `peso`) STORED
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Despejando dados para a tabela `produtos_confeitaria`
--

INSERT INTO `produtos_confeitaria` (`id`, `nome`, `preco_por_grama`, `peso`) VALUES
(1, 'Bolo de chocolate ', 20.00, 0.50);

--
-- Índices para tabelas despejadas
--

--
-- Índices de tabela `produtos_confeitaria`
--
ALTER TABLE `produtos_confeitaria`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT para tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `produtos_confeitaria`
--
ALTER TABLE `produtos_confeitaria`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
