-- phpMyAdmin SQL Dump
-- version 4.8.3
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 15-12-2018 a las 00:03:40
-- Versión del servidor: 10.1.37-MariaDB
-- Versión de PHP: 7.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `eremasinprel`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `accounting_catalog`
--

CREATE TABLE `accounting_catalog` (
  `id` int(11) NOT NULL,
  `code` varchar(45) NOT NULL,
  `parent` varchar(45) NOT NULL,
  `name` varchar(300) NOT NULL,
  `classification` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `accounting_catalog`
--

INSERT INTO `accounting_catalog` (`id`, `code`, `parent`, `name`, `classification`) VALUES
(1, '1', '', 'Activo', 'Crédito'),
(2, '2', '', 'Pasivo', 'Débito'),
(3, '3', '', 'Capital', 'Crédito'),
(4, '4', '', 'Costo', 'Débito'),
(5, '11', '1', 'Activo Circulante', 'Crédito'),
(6, '1101', '11', 'Cuentas por cobrar', 'Crédito'),
(7, '1102', '11', 'Terrenos', 'Crédito'),
(8, '21', '2', 'Ventas', 'Debito'),
(14, '1103', '11', 'Capital Social o Patrimonio', 'Crédito'),
(15, '1104', '11', 'Efectivo y Equivalente', 'Débito'),
(16, '110401', '1104', 'Bancos', 'Crédito'),
(17, '11040101', '110401', 'Banco Agricola', 'Crédito'),
(18, '1104010101', '11040101', 'Cuenta Corriente', 'Crédito'),
(19, '11040102', '110401', 'Banco Cuscatlán', 'Crédito'),
(20, '1104010201', '11040102', 'Cuenta Corriente', 'Crédito'),
(21, '11040103', '110401', 'Banco Promerica', 'Crédito'),
(22, '1104010301', '11040103', 'Cuenta corriente', 'Crédito');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `departments`
--

CREATE TABLE `departments` (
  `id` int(11) NOT NULL,
  `nombre` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `departments`
--

INSERT INTO `departments` (`id`, `nombre`) VALUES
(1, 'Usulután'),
(2, 'San Miguel'),
(3, 'San Salvador'),
(4, 'San Vicente'),
(5, 'Ahuachapán'),
(6, 'La unión'),
(7, 'La Libertad'),
(8, 'Santa Ana'),
(9, 'Cabañas');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `inventory`
--

CREATE TABLE `inventory` (
  `id` int(11) NOT NULL,
  `description` varchar(200) NOT NULL,
  `qty` int(11) NOT NULL,
  `unit` varchar(45) NOT NULL,
  `group` varchar(45) NOT NULL,
  `warehouse` varchar(45) NOT NULL,
  `code` varchar(45) NOT NULL,
  `price` decimal(10,4) NOT NULL,
  `cost` decimal(10,4) NOT NULL,
  `picture_path` varchar(45) NOT NULL,
  `minimum` int(11) NOT NULL,
  `ingress_date` date NOT NULL,
  `sale_date` date NOT NULL,
  `accounting_code` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `inventory`
--

INSERT INTO `inventory` (`id`, `description`, `qty`, `unit`, `group`, `warehouse`, `code`, `price`, `cost`, `picture_path`, `minimum`, `ingress_date`, `sale_date`, `accounting_code`) VALUES
(1, 'Fibra ADSS de 48 hilos doble chaqueta', 10050, 'mts', 'Fibra Óptica ADSS', 'Central', '8128191', '1.4501', '0.9821', '8128191.jpg', 0, '2018-11-22', '2018-11-22', '7812718'),
(2, 'Fibra GYXTW-B1 de 4 hilos armada', 15091, 'mts', 'Fibra Óptica ADSS', 'Central', '710129', '0.5221', '0.4141', '710129.jpg', 0, '2018-11-22', '2018-11-22', '718281'),
(3, 'Fibra óptica GYXTW de 6 hilos armada', 10012, 'mts', 'Fibra Óptica ADSS', 'Central', '81291781', '0.4121', '0.3456', '81291781.17', 0, '2018-11-22', '2018-11-22', '87129109');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `municipies`
--

CREATE TABLE `municipies` (
  `idMunicipio` int(11) NOT NULL,
  `nombre` varchar(25) NOT NULL,
  `id` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `municipies`
--

INSERT INTO `municipies` (`idMunicipio`, `nombre`, `id`) VALUES
(4, 'Chinameca', 2),
(9, 'Quelepa', 2),
(17, 'San Jacinto', 3),
(20, 'Nejapa', 3),
(23, 'Batres', 1),
(24, 'Ereguiste', 8),
(25, 'Ereguayquin', 1);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `neighborhood`
--

CREATE TABLE `neighborhood` (
  `idColonia` int(11) NOT NULL,
  `nombre` varchar(25) NOT NULL,
  `idMunicipio` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `neighborhood`
--

INSERT INTO `neighborhood` (`idColonia`, `nombre`, `idMunicipio`) VALUES
(5, 'Col Chinameca 1', 4),
(12, 'Lot El Sol', 9),
(14, 'Barrio Batres pasaje 1', 23),
(15, 'Colonia el porvenir', 23),
(16, 'Colonia el pedregal', 24),
(17, 'Colonia la wija1', 24),
(20, 'Col la hamaca', 4);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `providers`
--

CREATE TABLE `providers` (
  `id_proveedor` int(11) NOT NULL,
  `nombre` varchar(45) NOT NULL,
  `nit` varchar(20) NOT NULL,
  `nrc` varchar(10) NOT NULL,
  `direccion` varchar(45) NOT NULL,
  `giro` varchar(45) NOT NULL,
  `categoria` varchar(45) NOT NULL,
  `nacionalidad` varchar(20) NOT NULL,
  `telefono` varchar(20) NOT NULL,
  `correo_electronico` varchar(45) NOT NULL,
  `representante` varchar(45) NOT NULL,
  `cuenta_catalogo` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Volcado de datos para la tabla `providers`
--

INSERT INTO `providers` (`id_proveedor`, `nombre`, `nit`, `nrc`, `direccion`, `giro`, `categoria`, `nacionalidad`, `telefono`, `correo_electronico`, `representante`, `cuenta_catalogo`) VALUES
(1, 'Proveedora PC visión', '0021-548556-663-7', '2001147', 'Colonia la cruz, Usulután, El Salvador', 'Tecnología', 'Monitores para PC', 'Nicaraguence', '7022-1905', 'proveedora@correo.com', 'Juan Martínez,  7896-6415', '1102'),
(2, 'Telmex S.A de C.V', '4632-123456-782-0', '896200', 'México CA', 'Artículos de limpieza', 'Artículos para limpiar ventanas', 'Mexicano', '7841-3362', 'eremas@hotmail.com', 'Manuel Menjivar, 2624-5611', '3322'),
(3, 'AT&T', '1487-587875-500-1', '00456-00dd', 'Washington D.C, Estados Unidos', 'Telecomunicaciones', 'Cables para modems', 'Estadounidense', '1800-400-02', 'ahorasi@gmail.com', 'Diego Herrera 7022-1905', '1120'),
(4, 'Cable Visión Usulután', '0024-540054-966-1', '879000', 'Barrio la Merced, Usulután', 'Telecomunicaciones', 'Antenas de recepción de señal', 'Salvadoreña', '2624-8300', 'cablesat@gmail.com', 'Diego Herrera 7022-1905', '3300'),
(5, 'Microsoft', '3994-0045-796-1', '8955000', 'Palo alto, california, Estados Unidos', 'Tecnología', 'Servidores', 'Estadounidense', '1900-445-05', 'microsoft@billgates.com', 'Bill Gates 899-000', '7711'),
(6, 'Apple inc', '0184-63200-266-2', '00145555', 'Cupertino, California', 'Tecnología', 'Smartphones', 'Estadounidense', '1800-8978', 'appleinc@gmail.com', 'Ana 1800457', '5590'),
(7, 'Google inc', '1221-480072-200-9', '12003366', 'Sillicon Valley', 'Tecnología', 'Robotica', 'Estadounidense', '7884-4551', 'googleinc@gmail.com', 'Antonio 78956630', '4455'),
(8, 'Confecciones Santa Lucía', '1234-567891-200-8', '2088426', 'Jiquilisco, Usulután', 'Otros', 'Confección de uniformes de trabajo', 'Salvadoreña', '2624-8596', 'cofecciones@hotmail.com', 'N/A', '6644'),
(9, 'Juan Vazques', '4844-211544-746-0', '200400', 'Jiquilisco, Usulután', 'Otros', 'Confección de uniformes de trabajo', 'Salvadoreña', '2624-8596', 'cofecciones@hotmail.com', 'N/A', '6644'),
(10, 'Textiles San José', '1234-123456-123-1', '0180055', 'Colonia el por venir, pasaje lozano, casa #10', 'Otros', 'Telas para confección', 'Salvadoreña', '26240086', 'textiles@sanjose.com', 'Enrique García 26248899', '1100');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_country_departments`
--

CREATE TABLE `system_country_departments` (
  `id` int(11) NOT NULL,
  `name` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_country_departments`
--

INSERT INTO `system_country_departments` (`id`, `name`) VALUES
(1, 'San Salvador'),
(2, 'San Miguel'),
(3, 'Santa Ana');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_company_code`
--

CREATE TABLE `system_inventory_company_code` (
  `id` int(11) NOT NULL,
  `name` varchar(120) NOT NULL,
  `code` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_family_code`
--

CREATE TABLE `system_inventory_family_code` (
  `id` int(11) NOT NULL,
  `code` varchar(4) NOT NULL,
  `name` varchar(45) NOT NULL,
  `lastcode` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_inventory_family_code`
--

INSERT INTO `system_inventory_family_code` (`id`, `code`, `name`, `lastcode`) VALUES
(1, '04', '', '');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_product_family`
--

CREATE TABLE `system_inventory_product_family` (
  `id` int(11) NOT NULL,
  `name` varchar(300) NOT NULL,
  `abbreviated` varchar(45) NOT NULL,
  `code` varchar(10) NOT NULL,
  `counter` varchar(4) NOT NULL DEFAULT '0001'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_inventory_product_family`
--

INSERT INTO `system_inventory_product_family` (`id`, `name`, `abbreviated`, `code`, `counter`) VALUES
(1, 'Fibra Óptica ADSS', 'FOAS', '01', '0001'),
(2, 'Cable Coaxial Three Shield RG 6', 'CCRG6', '02', '0001'),
(3, 'Cable Coaxial Quad Shield RG6', 'CQRG6', '03', '0001');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_units`
--

CREATE TABLE `system_inventory_units` (
  `id` int(11) NOT NULL,
  `name` varchar(45) NOT NULL,
  `unit` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_inventory_units`
--

INSERT INTO `system_inventory_units` (`id`, `name`, `unit`) VALUES
(1, 'Metros', 'mts'),
(2, 'Kilometros', 'Km'),
(3, 'Unidad', 'Und'),
(4, 'Rollos', 'Rls'),
(5, 'Bolsa', 'Bsa'),
(6, 'Kilogramos', 'Kg');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_warehouses`
--

CREATE TABLE `system_inventory_warehouses` (
  `id` int(11) NOT NULL,
  `name` varchar(100) NOT NULL,
  `code` varchar(45) NOT NULL,
  `address` varchar(300) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_inventory_warehouses`
--

INSERT INTO `system_inventory_warehouses` (`id`, `name`, `code`, `address`) VALUES
(1, 'Central', '01', 'Pje 2, 3a Ave Norte entre 29 y 31 Calle Pte, No 311, Colonia Layco, San Salvador'),
(2, 'San Miguel', '02', 'Avenida Roosevelt No 2134');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_inventory_warehouse_code`
--

CREATE TABLE `system_inventory_warehouse_code` (
  `id` int(11) NOT NULL,
  `code` varchar(45) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_inventory_warehouse_code`
--

INSERT INTO `system_inventory_warehouse_code` (`id`, `code`) VALUES
(1, '03');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_taxes`
--

CREATE TABLE `system_taxes` (
  `id` int(11) NOT NULL,
  `iva` double NOT NULL,
  `pac` double NOT NULL,
  `cesc` double NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_taxes`
--

INSERT INTO `system_taxes` (`id`, `iva`, `pac`, `cesc`) VALUES
(1, 13, 1.75, 3);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `system_users`
--

CREATE TABLE `system_users` (
  `id` int(11) NOT NULL,
  `name` varchar(200) NOT NULL,
  `username` varchar(45) NOT NULL,
  `password` varchar(300) NOT NULL,
  `department` varchar(100) NOT NULL,
  `accesed` tinyint(4) NOT NULL,
  `lastdate` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `system_users`
--

INSERT INTO `system_users` (`id`, `name`, `username`, `password`, `department`, `accesed`, `lastdate`) VALUES
(1, 'Luis Marin', '1', '6b86b273ff34fce19d6b804eff5a3f5747ada4eaa22f1d49c01e52ddb7875b4b', 'Adminitrativa', 1, '2018-12-14'),
(5, 'L Marin', 'lmar', '3asefasefaf', 'Tecnica', 1, '2018-10-12');

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `accounting_catalog`
--
ALTER TABLE `accounting_catalog`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `code_UNIQUE` (`code`);

--
-- Indices de la tabla `departments`
--
ALTER TABLE `departments`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `inventory`
--
ALTER TABLE `inventory`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `code_UNIQUE` (`code`);

--
-- Indices de la tabla `municipies`
--
ALTER TABLE `municipies`
  ADD PRIMARY KEY (`idMunicipio`),
  ADD KEY `id` (`id`);

--
-- Indices de la tabla `neighborhood`
--
ALTER TABLE `neighborhood`
  ADD PRIMARY KEY (`idColonia`),
  ADD KEY `idMunicipio` (`idMunicipio`);

--
-- Indices de la tabla `providers`
--
ALTER TABLE `providers`
  ADD PRIMARY KEY (`id_proveedor`);

--
-- Indices de la tabla `system_country_departments`
--
ALTER TABLE `system_country_departments`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_inventory_company_code`
--
ALTER TABLE `system_inventory_company_code`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_inventory_family_code`
--
ALTER TABLE `system_inventory_family_code`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_inventory_product_family`
--
ALTER TABLE `system_inventory_product_family`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_inventory_units`
--
ALTER TABLE `system_inventory_units`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `unit_UNIQUE` (`unit`),
  ADD UNIQUE KEY `name_UNIQUE` (`name`);

--
-- Indices de la tabla `system_inventory_warehouses`
--
ALTER TABLE `system_inventory_warehouses`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name_UNIQUE` (`name`);

--
-- Indices de la tabla `system_inventory_warehouse_code`
--
ALTER TABLE `system_inventory_warehouse_code`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_taxes`
--
ALTER TABLE `system_taxes`
  ADD PRIMARY KEY (`id`);

--
-- Indices de la tabla `system_users`
--
ALTER TABLE `system_users`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `accounting_catalog`
--
ALTER TABLE `accounting_catalog`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT de la tabla `departments`
--
ALTER TABLE `departments`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT de la tabla `inventory`
--
ALTER TABLE `inventory`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `municipies`
--
ALTER TABLE `municipies`
  MODIFY `idMunicipio` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26;

--
-- AUTO_INCREMENT de la tabla `neighborhood`
--
ALTER TABLE `neighborhood`
  MODIFY `idColonia` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT de la tabla `providers`
--
ALTER TABLE `providers`
  MODIFY `id_proveedor` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT de la tabla `system_country_departments`
--
ALTER TABLE `system_country_departments`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `system_inventory_company_code`
--
ALTER TABLE `system_inventory_company_code`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `system_inventory_family_code`
--
ALTER TABLE `system_inventory_family_code`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `system_inventory_product_family`
--
ALTER TABLE `system_inventory_product_family`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `system_inventory_units`
--
ALTER TABLE `system_inventory_units`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT de la tabla `system_inventory_warehouses`
--
ALTER TABLE `system_inventory_warehouses`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT de la tabla `system_inventory_warehouse_code`
--
ALTER TABLE `system_inventory_warehouse_code`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `system_taxes`
--
ALTER TABLE `system_taxes`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `system_users`
--
ALTER TABLE `system_users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- Restricciones para tablas volcadas
--

--
-- Filtros para la tabla `municipies`
--
ALTER TABLE `municipies`
  ADD CONSTRAINT `municipies_ibfk_1` FOREIGN KEY (`id`) REFERENCES `departments` (`id`) ON DELETE CASCADE;

--
-- Filtros para la tabla `neighborhood`
--
ALTER TABLE `neighborhood`
  ADD CONSTRAINT `neighborhood_ibfk_1` FOREIGN KEY (`idMunicipio`) REFERENCES `municipies` (`idMunicipio`) ON DELETE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
