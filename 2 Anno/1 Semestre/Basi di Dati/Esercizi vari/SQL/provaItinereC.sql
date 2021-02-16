RICETTA (codice, nome, istruzioni, tipo)
TIPOLOGIA (id, nome)
ALIMENTO (id, nome, costo, gruppo_alimentare)
UTENSILE (id, nome, quantita_disponibile)
INGREDIENTI (ricetta, alimento, quantita)
USAUTENSILE (ricetta, utensile, numero)


--Trovare le tipologie di ricette che hanno un costo di cibo maggiore di quello medio di tutte le ricette di tipo ‘NOUVELLE CUISINE’;

CREATE VIEW somma AS
SELECT SUM(a.costo * i.quantita) som, i.ricetta, r.tipo 
FROM ALIMENTO a JOIN  INGREDIENTI i ON i.alimento = a.id 
JOIN RICETTA r ON r.codice  = i.ricetta 
GROUP BY r.codice;

SELECT s.ricetta 
FROM somma s 
WHERE s.som >=( SELECT AVG(s1.som)
                FROM somma s1
                WHERE s1.tipo = "NOUVELLECOUSINE"
               );

--Trovare le ricette che hanno usato tutti gli utensili;

SELECT r.codice
FROM Ricetta c
WHERE NOT EXISTS( SELECT *
                  FROM Utensile u
                  WHERE NOT EXISTS( SELECT *
                                    FROM Usautensile us 
                                    WHERE us.utensile = u.id 
                                    AND   us.ricetta = r.codice 
                                  )
                );

--Trovare le ricette che hanno usato utensili e quelle che non hanno usato utensili (scrivere solo una query piana)

SELECT codice, nome
FROM Ricetta;


--Aggiungere l’attributo ‘costo totale’ alla relazione RICETTA e scrivere un trigger che, 
--all’aggiunta di un ingrediente, aggiorni tale attributo.

ALTER TABLE(
    ADD COLUMN costo_totale INTO RICETTA
);

CREATE TRIGGER 
AFTER INSERT ON ingrediente
FOR EACH ROW
UPDATE ricetta 
SET costo_totale = costo_totale + ( SELECT (quantita * costo) somma
                                    FROM Ingredienti i JOIN Alimento a ON i.alimento = a.id 
                                    WHERE i.ricetta = new.ricetta 
                                    AND   i.alimento = new.alimento
                                  )
WHERE new.ricetta = codice; 