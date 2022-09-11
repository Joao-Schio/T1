import random



with open(("dna.ent"),"w") as w:
    for i in range(10000):
        for j in range(1499):
            print(random.choice("ATCG"),end="",file=w)
        print(random.choice("ATCG"),end=" ",file=w)
        



