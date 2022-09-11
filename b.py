
import os






def conta (str):
    AT = str.count("A") + str.count("T")
    CG = str.count("C") + str.count("G")

    return AT - CG





def inverte(str):
    saida = ''
    for i in range(len(str)):
        if str[i] == 'A':
            saida += 'T'
        if str[i] == 'T':
            saida += 'A'
        if str[i] == 'C':
            saida += 'G'
        if str[i] == 'G':
            saida += 'C'
    return saida









with open("dna.ent","r") as r:
    entrada = r.read().split()
    maior = 0
    saida1 = []
    saida2 = []
    mr = ''
    for i in range(len(entrada)):
        if conta(entrada[i]) > 0:
            if conta(entrada[i]) > maior:
                maior = conta(entrada[i])
                mr = entrada[i]
        if conta(entrada[i]) < 0:
            saida1.append(entrada[i])
        if inverte(entrada[i])[::-1] == entrada[i]:
            saida2.append(entrada[i])
        
    


    check1 = open("dna1.sai","r")
    check2 = open("dna2.sai","r")
    check3 = open("dna3.sai","r")


    cg = check1.read().split()
    Mrel = check2.read().split()
    palin = check3.read().split()



    






   

    print(cg == saida1)
   
    print(Mrel[0] == mr)

    print(palin == saida2)
  

    check1.close()
    check2.close()
    check3.close()
    
    os.remove("dna1.sai")
    os.remove("dna2.sai")
    os.remove("dna3.sai")
    

    
os.remove("dna.ent")


