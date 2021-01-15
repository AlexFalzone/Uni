Emergenza(id, idPersonaChiamante, data, ora, CAP, indirizzo, descrizione)
Persona(CF, nome, cognome)
Citta(id, nome, provincia)
Zona(idcitta, CAP)
Pericolosità(CAP, numeroChiamate, fasciaOraria)

--Trovare le città che hanno avuto un numero di chiamate d’emergenza minore a quello medio di tutte le città

CREATE VIEW chiamate_city AS
SELECT SUM(numeroChiamate) somma, Citta.id
FROM Citta c JOIN Zona z ON z.idcitta = c.id NATURAL JOIN Pericolosità p
GROUP BY c.id;

SELECT c_c.id
FROM chiamate_city c_c 
WHERE c_c.somma >= ( SELECT AVG(somma)
                     FROM chiamate_city
                   );


--Trovare le persone che hanno effettuato delle chiamate d’emergenza per tutte le città

CREATE VIEW pers_citta AS
SELECT DISTINCT c.id, p.CF
FROM persona p. e,Emergenza e, zona z, Citta c
WHERE p.cf = e.idPersonaChiamante 
AND   e.CAP = z.CAP 
AND   c.idcitta = z.idcitta;

SELECT p.CF
FROM Persona p 
WHERE NOT EXISTS( SELECT *
                  FROM Citta c
                  WHERE NOT EXISTS( SELECT *
                                    FROM pers_citta pc 
                                    WHERE p.CF = pc.CF 
                                    AND   c.id = p.id
                                  )
                );

--Implementare un vincolo di integrità che non consenta ad una persona di effettuare più di 5 chiamate d’emergenza nello stesso mese per la stessa città 

CREATE ASSERTION A1 AS
CHECK( 5 <= ALL( SELECT COUNT(*)
                 FROM Emergenza e NATURAL JOIN zona z JOIN citta c ON z.idcitta = c.id   
                 GROUP BY Emergenza.idPersonaChiamante, c.id
               )

     );

 --alternativfa all'asserzione con trigger

 CREATE TRIGGER T1
 AFTER INSERT Emergenza
 REFERENCING new AS newTable
 FOR EACH ROW
 DECLARE nchiamate NUMBER
 BEGIN 
    SELECT COUNT(*) INTO nchiamate
    FROM Emergenza e 
    WHERE e.idPersonaChiamante = new.idPersonaChiamante
    AND   MONTH(e.data) = MONTH(new.data) 
    IF nchiamate > 5 THEN
        DELETE FROM Emergenza e WHERE e.id = new.id
    END IF
END;