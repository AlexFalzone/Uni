Luogo(id, stato, citta)
Viaggio(id, datapartenza, datarientro)
Partecipante(idp,idv)
Tappa(idviaggio, idtappa, nome, numero_giorni,idluogo)
Persona(id,nome,cognome,frequentTraveler)

--Trovare le persone che hanno partecipato ad un numero di viaggi maggiore al numero medio di tutte le persone

CREATE VIEW media_viaggi AS
SELECT SUM(idv) somma, P.idp
FROM Partecipante P
GROUP BY P.idp;

SELECT MV.idp 
FROM media_viaggi MV
WHERE MV.somma >= (SELECT AVG(MV2.somma)
                   FROM media_viaggi MV
                  );

--Trovare le persone che hanno partecipato a tuti i viaggi della durata di 15 giorni

CREATE VIEW Giorni AS
SELECT V.*
FROM Viaggio V
WHERE datarientro - datapartenza = 15;

SELECT P.id 
FROM Persona P
WHERE NOT EXISTS (SELECT *
                  FROM Giorni G
                  WHERE NOT EXISTS(SELECT *
                                   FROM Partecipante PA 
                                   WHERE PA.idp = P.id 
                                   AND   PA.idv = G.id
                                  ) 
                 );

--Implementare un vincolo di integrità che non consenta di avere più di 5 tappe per ogni viaggio	

CREATE ASSERTION A1 AS
    CHECK( 5 >= (SELECT COUNT(*)
                FROM Tappa 
                GROUP BY idviaggio 
                )
         ); 

--Implementare un trigger elegga a frequentTraveler le persone che hanno fatto più di 10 viaggi nello stesso anno 

CREATE TRIGGER T1
AFTER UPDATE ON Partecipante 
FOR EACH ROW
WHEN 10 <(SELECT COUNT(*)
          FROM Partecipante p
          WHERE p.id = new.id
          GROUP BY idp;
         )
UPDATE Persona 
SET frequentTraveler = TRUE
WHERE Persona.id = new.id;
