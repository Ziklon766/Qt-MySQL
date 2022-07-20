-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Июл 01 2022 г., 15:11
-- Версия сервера: 5.6.51
-- Версия PHP: 7.1.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `autoroom`
--

-- --------------------------------------------------------

--
-- Структура таблицы `brends`
--

CREATE TABLE `brends` (
  `brend_id` int(11) NOT NULL,
  `brend_name` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `brends`
--

INSERT INTO `brends` (`brend_id`, `brend_name`) VALUES
(1, 'BMW'),
(2, 'Mercedes Benz'),
(3, 'Mazda'),
(4, 'Ford'),
(5, 'Audi'),
(6, 'Geely'),
(7, 'Honda'),
(8, 'Hyudai'),
(9, 'Kia'),
(10, 'Jaguar'),
(11, 'Land Rover'),
(12, 'Nissan'),
(13, 'Opel'),
(14, 'Renault'),
(15, 'Skoda'),
(16, 'Subaru'),
(17, 'Yamaha'),
(18, 'КАМАЗ');

-- --------------------------------------------------------

--
-- Структура таблицы `clients`
--

CREATE TABLE `clients` (
  `client_id` int(11) NOT NULL,
  `name` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `surname` varchar(50) COLLATE utf8mb4_unicode_ci NOT NULL,
  `phone` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `password` text COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `clients`
--

INSERT INTO `clients` (`client_id`, `name`, `surname`, `phone`, `email`, `password`) VALUES
(1, 'Алексей', 'Алешин', '8 800 555-35-35', '', ''),
(2, 'Дмитрий', 'Видящев', '8 911 120-20-29', '', ''),
(3, 'Денис', 'Смоленский', '89211284563', '', ''),
(4, 'Сергей', 'Никифоров', '+79815678998', '', ''),
(5, 'Татьяна', 'Александрова ', '8 911 450 66 67', '', ''),
(6, 'Артур', 'Пирожков', '9720507165', '', ''),
(9, 'Мария', 'Новикова', '89523568775', '', ''),
(10, 'Иван', 'Сидоров', '+7 (911) 158-8013', '', ''),
(11, 'Александр', 'Малиновский', '+7-991-434-33-20', '', ''),
(12, 'Елена', 'Сергеева', '8 (963) 777-23-30', '', ''),
(13, 'Евгения', 'Тарасова', '55555', 'mail.com', '123'),
(15, 'Юрий', 'Антонов', '8 (981) 325-93-90', '', ''),
(17, 'Дарья', 'Скворцова', '8 963 760-45-54', 'post@mail.ru', 'password');

-- --------------------------------------------------------

--
-- Структура таблицы `companys`
--

CREATE TABLE `companys` (
  `company_id` int(11) NOT NULL,
  `name` varchar(100) COLLATE utf8mb4_unicode_ci NOT NULL,
  `address` varchar(200) COLLATE utf8mb4_unicode_ci NOT NULL,
  `phone` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `companys`
--

INSERT INTO `companys` (`company_id`, `name`, `address`, `phone`) VALUES
(1, 'ООО \"Альфа Моторс\"', 'улица Курчатова 27', '8 800 555-35-35'),
(2, 'ООО \"Компания\"', 'Проспект Большевиков 128', '567-52-52'),
(4, 'ООО \"АВТОРЕСУРС\"', 'Невский пр-к 128', '968-728-79-99	'),
(5, 'MIDAS-PARTS', 'Москва, Главная улю 54', '926-328-999-2	'),
(6, 'KIA MOTORS', 'Пулковское шоссе 36', '  903-263-84-44	'),
(7, 'ООО \"Автозум\"', 'Краснодар, Декабристов 7', '495-924-46-78	'),
(8, 'Т-МОТОРС SKODA', 'ул Космонавтов 42', '985-400-05-64	'),
(9, 'GERMANAUTO', 'Берлин, площадь свободы 2', '917-566-69-62	'),
(10, 'АВТОСТРАЙК', 'Красносельское шоссе 25', '502-60-44'),
(11, 'ФОРСАЖ', 'Счастливая 12', '455-60-00');

-- --------------------------------------------------------

--
-- Структура таблицы `consignment`
--

CREATE TABLE `consignment` (
  `treaty_num` int(11) DEFAULT NULL,
  `product_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `ord_num` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `consignment`
--

INSERT INTO `consignment` (`treaty_num`, `product_id`, `amount`, `ord_num`) VALUES
(32, 10, 2, NULL),
(NULL, 12, 1, 11),
(NULL, 14, 1, 11),
(33, 22, 1, NULL),
(33, 15, 1, NULL),
(33, 8, 3, NULL);

-- --------------------------------------------------------

--
-- Структура таблицы `orders`
--

CREATE TABLE `orders` (
  `order_num` int(11) NOT NULL,
  `client_id` int(11) NOT NULL,
  `date` date NOT NULL,
  `sum` int(11) NOT NULL,
  `done` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `orders`
--

INSERT INTO `orders` (`order_num`, `client_id`, `date`, `sum`, `done`) VALUES
(11, 17, '2000-01-01', 10001000, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `products`
--

CREATE TABLE `products` (
  `prod_id` int(11) NOT NULL,
  `brend_id` int(11) NOT NULL,
  `model` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL,
  `V` float NOT NULL,
  `fuel` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `transmis` varchar(2) COLLATE utf8mb4_unicode_ci NOT NULL,
  `power` int(11) NOT NULL,
  `year` int(11) NOT NULL,
  `unit` varchar(10) COLLATE utf8mb4_unicode_ci NOT NULL,
  `color_body` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `color_in` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `material` varchar(30) COLLATE utf8mb4_unicode_ci NOT NULL,
  `price` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `type` varchar(20) COLLATE utf8mb4_unicode_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `products`
--

INSERT INTO `products` (`prod_id`, `brend_id`, `model`, `V`, `fuel`, `transmis`, `power`, `year`, `unit`, `color_body`, `color_in`, `material`, `price`, `amount`, `type`) VALUES
(8, 2, 'E-class', 2.4, 'бензин', 'AT', 220, 2018, 'задний', 'черный', 'черный', 'кожа', 5000000, 3, 'Легковой'),
(10, 3, '3', 1.8, 'бензин', 'AT', 124, 2007, 'передний', 'синий', 'черный', 'кожа', 370000, 0, 'Легковой'),
(12, 5, 'A4', 1.2, 'бензин', 'MT', 50, 1900, 'передний', 'Красный', 'Коричневый', 'Кожа', 10000000, 0, 'Легковой'),
(13, 10, 'XF', 2, 'бензин', 'AT', 240, 2022, 'полный', 'черный', 'красный', 'кожа', 7500000, 0, 'Легковой'),
(14, 2, 'GLE', 3, 'бензин', 'AT', 360, 2022, 'полный', 'синий', 'черный', 'кожа', 10000000, 0, 'Легковой'),
(15, 12, 'X-Trail', 1.2, 'бензин', 'MT', 50, 1900, 'передний', 'белыый', 'белый', 'ткань', 2300000, 1, 'Легковой'),
(17, 7, 'CMX1100', 1.2, 'бензин', 'AT', 90, 2021, 'задний', 'Красный', 'Черный', 'Кожа', 400000, 0, 'Мотоцикл'),
(18, 6, 'Emgrand', 1.6, 'бензин', 'MT', 132, 2015, 'передний', 'Белый', 'Черный', 'Кож зам', 400000, 0, 'Легковой'),
(20, 5, 'EX', 1.2, 'дизель', 'MT', 50, 2022, 'полный', 'Синий', 'Белый', '', 2000000, 0, 'Водный'),
(22, 18, 'Самосвал', 6.5, 'дизель', 'Гр', 450, 2008, 'задний', 'Голубой', 'Серый', 'Ткань', 1300000, 1, 'Грузовой');

-- --------------------------------------------------------

--
-- Структура таблицы `treatys`
--

CREATE TABLE `treatys` (
  `num_treaty` int(11) NOT NULL,
  `company_id` int(11) NOT NULL,
  `date` date NOT NULL,
  `date_comp` date NOT NULL,
  `sum` int(11) NOT NULL,
  `paid` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `treatys`
--

INSERT INTO `treatys` (`num_treaty`, `company_id`, `date`, `date_comp`, `sum`, `paid`) VALUES
(32, 10, '2000-01-01', '2000-01-01', 740000, 1),
(33, 2, '2000-01-01', '2000-01-01', 18600000, 8600000);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `brends`
--
ALTER TABLE `brends`
  ADD PRIMARY KEY (`brend_id`);

--
-- Индексы таблицы `clients`
--
ALTER TABLE `clients`
  ADD PRIMARY KEY (`client_id`);

--
-- Индексы таблицы `companys`
--
ALTER TABLE `companys`
  ADD PRIMARY KEY (`company_id`);

--
-- Индексы таблицы `consignment`
--
ALTER TABLE `consignment`
  ADD KEY `treaty_num` (`treaty_num`),
  ADD KEY `product_id` (`product_id`),
  ADD KEY `num_ord` (`ord_num`);

--
-- Индексы таблицы `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`order_num`),
  ADD KEY `client_id` (`client_id`);

--
-- Индексы таблицы `products`
--
ALTER TABLE `products`
  ADD PRIMARY KEY (`prod_id`),
  ADD KEY `brend_id` (`brend_id`);

--
-- Индексы таблицы `treatys`
--
ALTER TABLE `treatys`
  ADD PRIMARY KEY (`num_treaty`),
  ADD KEY `company_id` (`company_id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `brends`
--
ALTER TABLE `brends`
  MODIFY `brend_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=19;

--
-- AUTO_INCREMENT для таблицы `clients`
--
ALTER TABLE `clients`
  MODIFY `client_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT для таблицы `companys`
--
ALTER TABLE `companys`
  MODIFY `company_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT для таблицы `orders`
--
ALTER TABLE `orders`
  MODIFY `order_num` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT для таблицы `products`
--
ALTER TABLE `products`
  MODIFY `prod_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT для таблицы `treatys`
--
ALTER TABLE `treatys`
  MODIFY `num_treaty` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=34;

--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `consignment`
--
ALTER TABLE `consignment`
  ADD CONSTRAINT `consignment_ibfk_2` FOREIGN KEY (`treaty_num`) REFERENCES `treatys` (`num_treaty`) ON UPDATE CASCADE,
  ADD CONSTRAINT `consignment_ibfk_3` FOREIGN KEY (`product_id`) REFERENCES `products` (`prod_id`) ON UPDATE CASCADE,
  ADD CONSTRAINT `consignment_ibfk_4` FOREIGN KEY (`ord_num`) REFERENCES `orders` (`order_num`) ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `orders`
--
ALTER TABLE `orders`
  ADD CONSTRAINT `orders_ibfk_4` FOREIGN KEY (`client_id`) REFERENCES `clients` (`client_id`) ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `products`
--
ALTER TABLE `products`
  ADD CONSTRAINT `products_ibfk_8` FOREIGN KEY (`brend_id`) REFERENCES `brends` (`brend_id`) ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `treatys`
--
ALTER TABLE `treatys`
  ADD CONSTRAINT `treatys_ibfk_3` FOREIGN KEY (`company_id`) REFERENCES `companys` (`company_id`) ON UPDATE CASCADE;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
