def printl(list1):
    for i in list1:
        print(i)
        
def printExpression(constantList, filepointer):
    for i in constantList:
        if(i[0]=="="):
            print(i[3],i[0],i[1])
            filepointer.write("%s %s %s\n"%(i[3],i[0],i[1]))
        elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
            print(i[3],"=",i[1],i[0],i[2])
            filepointer.write("%s %s %s %s %s\n"%(i[3],"=",i[1],i[0],i[2]))
        elif(i[0] in ["IF","GOTO","LABEL","not"]):
            
            if(i[0]=="IF"):
                print(i[0],i[1],"GOTO",i[3])
                filepointer.write("%s %s %s %s\n" %(i[0],i[1],"GOTO",i[3]))
            if(i[0]=="GOTO"):
                print(i[0],i[1])
                filepointer.write("%s %s\n"%(i[0],i[1]))
            if(i[0]=="LABEL"):
                filepointer.write("%s %s\n"%(i[1], ":"))
                print(i[1],":")
            if(i[0]=="not"):
                print(i[3],"=",i[0],i[1])
                filepointer.write("%s %s %s %s\n"%(i[3],"=",i[0],i[1]))
def existslabel(lines, i):
    if(i == 0):
        return 0
    while(i>=0):
        if(len(lines[i].split()) == 2):
            return 1
        i = i - 1
    return 0
        
def exists_lhs(lines, variable, start, end):
    for i in range(start, end):
        if(lines[i].split()[0] == variable):
            return 1
    return 0
def findLoopLines(lines):
    gotoindex = dict()
    loopblock = []
    labelindex = dict()
    for i in range(len(lines)):
        lines[i] = lines[i].strip("\n")
        if(len(lines[i].split())==2 and lines[i].split()[0] == 'goto'):
            gotoindex[lines[i].split()[1]] = i
        if(len(lines[i].split()) == 2 and lines[i].split()[1] == ':'):
            labelindex[lines[i].split()[0]] = i
    for key in gotoindex:
        if(gotoindex[key]>labelindex[key]):
            loopblock.append([labelindex[key], gotoindex[key]])
    return loopblock
def loopMotion(lines):
    for i in range(len(lines)):
        lines[i] = lines[i].strip("\n")
    loopblock = findLoopLines(lines)
    for i in loopblock:
        initloc = i[0]
        for j in range(i[0], i[1]):
            if(len(lines[j].split()) == 3 and lines[j].split()[2].isdigit()):
                temp = lines.pop(j)
                lines.insert(initloc, temp)
                initloc+=1
            if(len(lines[j].split())==3):
                arg = lines[j].split()[2]
                if(not exists_lhs(lines, arg, initloc, i[1])):
                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1
            if(len(lines[j].split()) == 5):
                arg1 = lines[j].split()[2]
                arg2 = lines[j].split()[4]
                
                if(arg1.isdigit() and arg2.isdigit()):
                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1
                elif(arg1.isdigit()):
                    if(not exists_lhs(lines, arg2, initloc, i[1])):
                       temp = lines.pop(j)
                       lines.insert(i[0], temp)
                elif(arg2.isdigit()):
                    if(not exists_lhs(lines, arg1, initloc, i[1])):
                        temp = lines.pop(j)
                        lines.insert(initloc, temp)
                        initloc+=1
                else:
                    if(not exists_lhs(lines, arg1, initloc, i[1]) and not exists_lhs(lines, arg2, initloc, i[1])):
                        temp  = lines.pop(j)
                        lines.insert(initloc, temp)
                        initloc+=1
                        
                        
            
                
                
    printl(lines)
    return lines, loopblock
    
        
    
def elimDeadCode(lines):
    flag = 0
    newlines = []
    for i in range(len(lines)):
        lines[i] = lines[i].strip("\n")
        outflag = 0
        if(existslabel(lines, i) == 1):
            
            
            newlines.append(lines[i])
            continue
        if(len(lines[i].split()) == 5 or len(lines[i].split()) == 3):

            lhs = lines[i].split()[0]
            
            for j in range(i+1, len(lines)):

                if(len(lines[j].split()) == 5):
                    rhs1 = lines[j].split()[2]
                    rhs2 = lines[j].split()[4]
                    if(rhs1 == lhs or rhs2 == lhs):
                        outflag = 1
                        flag = 1
                        break

                elif(len(lines[j].split()) == 3):

                    rhs = lines[j].split()[2]

                    if(rhs == lhs):
                        outflag =1
                        flag = 1
                        break
                
                elif(len(lines[j].split()) == 4):
                    rhs = lines[j].split()[1]
                    l1 = ""
                    l2 = ""
                    fl = 0
                    for x in rhs:
                        if x in [">", "<", ">=", "<=", "==", "!="]:
                            fl = 1
                        if(fl == 0):
                            l1 = l1 + x
                        if(fl == 1):
                            l2 = l2 + x
                    if(l1 == lhs or l2 == lhs):
                        flag = 1
                        outflag = 1
                        break
                else:

                    continue

            if(outflag == 1):
                
                newlines.append(lines[i])
                    
                    
                
        else:
            newlines.append(lines[i])
            continue
    
    return newlines

def constantFolding(lines, blocks):
    tempdict = dict()
    constantList = []
    fullList = []
    print("Constant Folding Quadruples")
    print("___________________________")
    k = 0
    for i in lines:
        
        i = i.strip("\n")
        if k in blocks:
            if(len(i.split()) == 3):
                print("=", rhs, "NULL", lhs)
                lhs, ass, rhs = i.split()
                constantList.append(["=", rhs, "NULL", lhs])
                fullList.append(["=", rhs, "NULL", lhs])
            elif(len(i.split()) == 5):
                print(operator,arg1,arg2,lhs)
                lhs, ass, arg1, operator, arg2 = i.split()
                constantList.append([operator, arg1, arg2, lhs])
            elif(len(i.split()) == 2):
                arg1, arg2 = i.split()
                if(arg1 == "goto"):
                    print("GOTO", arg2)
                    constantList.append(["GOTO", arg2, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                else:
                    print("LABEL", arg1)
                    constantList.append(["LABEL", arg1, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
            else:
                cond, arg1, gt, label = i.split();
                print("IF", arg1, "GOTO", label)
                constantList.append(["IF", arg1, "GOTO", label])
                fullList.append(["IF", arg1, "GOTO", label])
                
        else:
            if(len(i.split()) == 3):
                lhs, ass, rhs = i.split()
                if(rhs.isdigit()):
                    tempdict[lhs] = rhs;
                    print("=", rhs, "NULL", lhs);
                    constantList.append(["=", rhs, "NULL", lhs])
                    fullList.append(["=", rhs, "NULL", lhs])
                else:
                    if(rhs in tempdict):
                        tempdict[lhs] = tempdict[rhs]
                        print("=", tempdict[rhs], "NULL", lhs)
                        constantList.append(["=", tempdict[rhs], "NULL", lhs])
                        fullList.append(["=", tempdict[rhs], "NULL", lhs])
                    else:
                        print("=", rhs, "NULL", lhs)
                        constantList.append(["=", rhs, "NULL", lhs])
                        fullList.append(["=", rhs, "NULL", lhs])
                    
                    
            elif(len(i.split()) == 5):
                lhs, ass, arg1, operator, arg2 = i.split()
                if(operator in ["+", "-", "*", "/"]):
                    if(arg1.isdigit() and arg2.isdigit()):
                        result = eval(arg1+operator+arg2)
                        tempdict[lhs] = result
                        print("=", result, "NULL", lhs)
                        constantList.append(["=", result, "NULL", lhs])
                        fullList.append(["=", result, "NULL", lhs])
                    elif(arg1.isdigit()):
                        if(arg2 in tempdict):
                            result = eval(arg1+operator+str(tempdict[arg2]))
                            tempdict[lhs] = result
                            print("=", result, "NULL", lhs)
                            constantList.append(["=", result, "NULL", lhs])
                            fullList.append(["=", result, "NULL", lhs])
                        else:
                            print(operator, arg1, arg2, lhs)
                            constantList.append([operator, arg1, arg2, lhs])
                            fullList.append([operator, arg1, arg2, lhs])
                    elif(arg2.isdigit()):
                    
                        if(arg1 in tempdict):
                        
                            result = eval(str(tempdict[arg1])+operator+arg2)
                            tempdict[lhs] = result
                            print("=",result,"NULL",lhs)
                            constantList.append(["=",result,"NULL",lhs])
                            fullList.append(["=",result,"NULL",lhs])
                        else:
                            print(operator,arg1,arg2,lhs)
                            constantList.append([operator,arg1,arg2,lhs])
                            fullList.append([operator,arg1,arg2,lhs])
                    else:
                        flag1=0
                        flag2=0
                        arg1Res = arg1
                        if(arg1 in tempdict):
                            arg1Res = str(tempdict[arg1])
                            flag1 = 1
                        arg2Res = arg2
                        if(arg2 in tempdict):
                            arg2Res = str(tempdict[arg2])
                            flag2 = 1
                        if(flag1==1 and flag2==1):
                            result = eval(arg1Res+operator+arg2Res)
                            tempdict[lhs] = result
                            print("=",result,"NULL",lhs) 
                            constantList.append(["=",result,"NULL",lhs])
                            fullList.append(["=",result,"NULL",lhs])
                        else:
                            print(operator,arg1Res,arg2Res,lhs)
                            constantList.append([operator,arg1Res,arg2Res,lhs])
                            fullList.append([operator,arg1Res,arg2Res,lhs])
            
                elif(operator=="="):
                    if(arg1.isdigit()):
                        tempdict[lhs]=arg1
                        print("=",arg1,"NULL",lhs)
                        constantList.append(["=",arg1,"NULL",lhs])
                        fullList.append(["=",arg1,"NULL",lhs])
                    else:
                        if(arg1 in tempdict):
                            print("=",tempdict[arg1],"NULL",lhs)
                            constantList.append(["=",tempdict[arg1],"NULL",lhs])
                            fullList.append(["=",tempdict[arg1],"NULL",lhs])
                        else:
                            print("=",arg1,"NULL",lhs)
                            constantList.append(["=",arg1,"NULL",lhs])
                            fullList.append(["=",arg1,"NULL",lhs])
    
                else:
                    print(operator,arg1,arg2,lhs)
                    constantList.append([operator,arg1,arg2,lhs])
                    fullList.append([operator,arg1,arg2,lhs])
            elif(len(i.split()) == 2):
                arg1, arg2 = i.split()
                if(arg1 == 'goto'):
                    print("GOTO", arg2)
                    constantList.append(["GOTO", arg2, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                else:
                    print("LABEL", arg1)
                    constantList.append(["LABEL", arg1, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                
            else:
                cond, arg1, gt, label = i.split();
                print("IF", arg1, "GOTO", label)
                constantList.append(["IF", arg1, "GOTO", label])
                fullList.append(["IF", arg1, "GOTO", label])
        k+=1
    
    newlist = []
    for i in constantList:
        if(i[3][0] == 't' and i[3][1:len(i[3])].isdigit()):
            continue
        else:
            newlist.append(i)
    return newlist, fullList





fin = open("icg.txt", "r")
fout = open("p5out.txt", "w")
lines = fin.readlines()
print("Loop Invariant Code Motion")
print("__________________________")
lines, loopblock = loopMotion(lines)        
print("Dead Code Elimination")
print("_____________________")
lines = elimDeadCode(lines)
printl(lines)
looplines = findLoopLines(lines)
loop = []
for i in range(len(looplines)):
    for j in range(looplines[i][0], looplines[i][1]+1):
        loop.append(j)

constantList, fullList = constantFolding(lines, loop)
print("\n")
print("Constant Folded Expression")
print("__________________________")
printExpression(constantList, fout)
fin.close()
fout.close()
#printl(constantList)



