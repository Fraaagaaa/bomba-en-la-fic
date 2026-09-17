-- ----------------------------------------------------------------------------
-- Put here INSERT statements for inserting data required by the application
-- in the "paproject" database.
-------------------------------------------------------------------------------
DELETE FROM Purchase;
DELETE FROM Session;
DELETE FROM Saloon;
DELETE FROM Movie;
DELETE FROM User;

INSERT INTO User (userName, password, firstName, lastName, email, role)
VALUES ('viewer', '$2a$10$v.js2jCaX3xoKvkR6E2pbugMmZDBPlCAz2gA7EOIZhbkvsPFew/5u', 'Espectador', 'User', 'viewer@udc.es', 0);

INSERT INTO User (userName, password, firstName, lastName, email, role)
VALUES ('ticketseller', '$2a$10$v.js2jCaX3xoKvkR6E2pbugMmZDBPlCAz2gA7EOIZhbkvsPFew/5u', 'Taquillero', 'User', 'seller@udc.es', 1);

INSERT INTO Saloon (name, capacity) VALUES ('Sala Pequeña', 9);
INSERT INTO Saloon (name, capacity) VALUES ('Sala Grande', 15);

INSERT INTO Movie (title, summary, duration) VALUES ('Pelicula A', 'Resumen A', 120);
INSERT INTO Movie (title, summary, duration) VALUES ('Pelicula B', 'Resumen B', 90);


INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres)
VALUES (7.50, CONCAT(CURDATE(), ' 00:05:00'), 2, 1, 13);

INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres)
VALUES (8.50, CONCAT(CURDATE(), ' 23:55:00'), 1, 2, 9);

INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 1 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 1 DAY), 2, 2, 15);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 2 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 2 DAY), 2, 2, 15);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 3 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 3 DAY), 2, 2, 15);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 4 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 4 DAY), 2, 2, 15);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 5 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 5 DAY), 2, 2, 15);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 18:00:00'), INTERVAL 6 DAY), 1, 1, 9);
INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres) VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 21:00:00'), INTERVAL 6 DAY), 2, 2, 15);

INSERT INTO Purchase (ticketAmmount, purchaseDate, creditCard, recogidas, session_id, userId)
VALUES (1, NOW(), '1234567812345678', 0, 1, 1);

INSERT INTO Purchase (ticketAmmount, purchaseDate, creditCard, recogidas, session_id, userId)
VALUES (1, NOW(), '8765432187654321', 0, 1, 1);

-- E2E Tests

INSERT INTO User (userName, password, firstName, lastName, email, role)
VALUES ('testviewer', '$2a$10$v.js2jCaX3xoKvkR6E2pbugMmZDBPlCAz2gA7EOIZhbkvsPFew/5u', 'Espectador', 'Test', 'testviewer@udc.es', 0);

INSERT INTO User (userName, password, firstName, lastName, email, role)
VALUES ('testticketseller', '$2a$10$v.js2jCaX3xoKvkR6E2pbugMmZDBPlCAz2gA7EOIZhbkvsPFew/5u', 'Taquillero', 'Test', 'testticketseller@udc.es', 1);

INSERT INTO Session (price, sessionStartTime, saloon_id, movie_id, asientosLibres)
VALUES (7.00, DATE_ADD(CONCAT(CURDATE(), ' 01:00:00'), INTERVAL 1 DAY), 1, 1, 4);

INSERT INTO Purchase (ticketAmmount, purchaseDate, creditCard, recogidas, session_id, userId)
VALUES (
           2,
           NOW(),
           '1234567812345678',
           0,
           (SELECT id FROM Session WHERE sessionStartTime = DATE_ADD(CONCAT(CURDATE(), ' 01:00:00'), INTERVAL 1 DAY) LIMIT 1),
       (SELECT id FROM User WHERE userName = 'testviewer')
    );
