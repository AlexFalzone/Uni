CONTOCORRENTE(id_conto,saldo,data_apertura)
PRODOTTOFINANZIARIO(id_conto, id_prodotto,data_stipula,numero_rate,id_contraente)
PERSONA(id_persona,nome,cognome,data_nascita)
TITOLARECC(Id_persona,ID_conto)
TRANSAZIONE(id_contoIN,id_contoOUT,data,causale,dare_avere,importo)
TRANSAZIONEPRODOTTOFINANZIARIO(id_conto,data,causale ,importo,id_prodotto)

1.Trovare il cc con il saldo più alto

SELECT id_conto
FROM CONTOCORRENTE c1
WHERE NOT EXISTS( SELECT id_conto
                  FROM CONTOCORRENTE c2
                  WHERE c2.saldo > c1.saldo
                );

2.Trovare la persona che ha	il saldo totale	più	elevato 

SELECT id_persona, SUM(saldo) saldo_totale
FROM CONTOCORRENTE NATURAL JOIN TITOLARECC
GROUP BY id_persona 
HAVING saldo_totale >= ALL( SELECT id_persona, SUM(saldo) saldo_totale
                            FROM CONTOCORRENTE NATURAL JOIN TITOLARECC
                            GROUP BY id_persona
                          );

3.Trovare il prodotto finanziario che ha più rate

SELECT id_prodotto
FROM PRODOTTOFINANZIARIO PF1
WHERE NOT EXISTS( SELECT *
                  FROM PRODOTTOFINANZIARIO PF2
                  WHERE PF2 > PF1
                );