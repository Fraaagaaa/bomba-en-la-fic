DROP TABLE Purchase;
DROP TABLE Session;
DROP TABLE Saloon;
DROP TABLE Movie;
DROP TABLE User;

CREATE TABLE User (
    id BIGINT NOT NULL AUTO_INCREMENT,
    userName VARCHAR(60) COLLATE latin1_bin NOT NULL,
    password VARCHAR(60) NOT NULL,
    firstName VARCHAR(60) NOT NULL,
    lastName VARCHAR(60) NOT NULL,
    email VARCHAR(60) NOT NULL,
    role TINYINT NOT NULL,
    CONSTRAINT UserPK PRIMARY KEY (id),
    CONSTRAINT UserNameUniqueKey UNIQUE (userName)
) ENGINE = InnoDB;

CREATE INDEX UserIndexByUserName ON User (userName);

CREATE TABLE Movie (
    id BIGINT NOT NULL AUTO_INCREMENT,
    title VARCHAR(200) NOT NULL,
    summary VARCHAR(2000) NOT NULL,
    duration INT NOT NULL,
    CONSTRAINT MoviePK PRIMARY KEY (id)
) ENGINE = InnoDB;

CREATE TABLE Saloon (
    id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(60) NOT NULL,
    capacity INT NOT NULL,
    CONSTRAINT SaloonPK PRIMARY KEY (id)
) ENGINE = InnoDB;

CREATE TABLE Session (
    id BIGINT NOT NULL AUTO_INCREMENT,
    price DECIMAL(11, 2) NOT NULL,
    sessionStartTime DATETIME NOT NULL,
    saloon_id BIGINT NOT NULL,
    movie_id BIGINT NOT NULL,
    asientosLibres INT NOT NULL,
    version BIGINT NOT NULL DEFAULT 0,
    CONSTRAINT SessionPK PRIMARY KEY (id),
    CONSTRAINT SessionSaloonIdFK FOREIGN KEY(saloon_id)
        REFERENCES Saloon (id),
    CONSTRAINT SessionMovieIdFK FOREIGN KEY(movie_id)
        REFERENCES Movie (id)
) ENGINE = InnoDB;

CREATE TABLE Purchase (
    id BIGINT NOT NULL AUTO_INCREMENT,
    ticketAmmount INT NOT NULL,
    purchaseDate DATETIME NOT NULL,
    creditCard VARCHAR(16) NOT NULL,
    recogidas TINYINT(1) DEFAULT 0, -- Booleano: 0 = false, 1 = true
    session_id BIGINT NOT NULL,
    userId BIGINT NOT NULL,
    CONSTRAINT PurchasePK PRIMARY KEY (id),
    CONSTRAINT PurchaseSessionIdFK FOREIGN KEY(session_id)
        REFERENCES Session (id),
    CONSTRAINT PurchaseUserIdFK FOREIGN KEY(userId)
        REFERENCES User (id)
) ENGINE = InnoDB;