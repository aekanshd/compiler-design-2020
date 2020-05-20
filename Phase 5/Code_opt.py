import time
def printl(list1):
    for i in list1:
        print(i)
        time.sleep(0.05)
        
def printExpression(constantList, filepointer):
    for i in constantList:
        if(i[0] == "A" and i[1] == "R" and i[2]=="R"):
            print(i)
            time.sleep(0.05)
            filepointer.write("%s\n"%(i))
        if(i[0]=="="):
            print(i[3],i[0],i[1])
            time.sleep(0.05)
            filepointer.write("%s %s %s\n"%(i[3],i[0],i[1]))
        elif(i[0] in ["+","-","*","/","==","<=","<",">",">="]):
            print(i[3],"=",i[1],i[0],i[2])
            time.sleep(0.05)
            filepointer.write("%s %s %s %s %s\n"%(i[3],"=",i[1],i[0],i[2]))
        elif(i[0] in ["IF","GOTO","LABEL","not", "ARR"]):
            
            if(i[0]=="IF"):
                print(i[0],i[1],"GOTO",i[3])
                time.sleep(0.05)
                filepointer.write("%s %s %s %s\n" %(i[0],i[1],"GOTO",i[3]))
            if(i[0]=="GOTO"):
                print(i[0],i[1])
                time.sleep(0.05)
                filepointer.write("%s %s\n"%(i[0],i[1]))
            if(i[0]=="LABEL"):
                filepointer.write("%s %s\n"%(i[1], ":"))
                print(i[1],":")
                time.sleep(0.05)
            if(i[0]=="not"):
                print(i[3],"=",i[0],i[1])
                time.sleep(0.05)
                filepointer.write("%s %s %s %s\n"%(i[3],"=",i[0],i[1]))
            if(i[0] == "ARR"):
                print(i[1], "=", i[3])
                time.sleep(0.05)
                filepointer.write("%s %s %s %s\n"%("ARR", i[0], "=", i[3]))
                
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
def exists_rhs(lines, lhs, start):
    for i in range(len(lines)-1, start-1, -1):
        if(len(lines[i].split()) == 5):
            rhs1 = lines[i].split()[2]
            rhs2 = lines[i].split()[4]
            if(rhs1 == lhs or rhs2 == lhs):              
                return i
        elif(len(lines[i].split()) == 3):
            rhs = lines[i].split()[2]
            if(rhs == lhs):
                return i
        elif(len(lines[i].split()) == 4):
            rhs = lines[i].split()[1]
            l1 = ""
            l2 = ""
            fl = 0
            for x in rhs:
                if x in [">", "<", "=", "!"]:
                    fl = 1
                    continue
                if (x == "="):
                    continue
                if(fl == 0):
                    l1 = l1 + x
                if(fl == 1):
                    l2 = l2 + x
            if(l1 == lhs or l2 == lhs):
                return i
    return -1
        
        
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
            
                
            if(len(lines[j].split()) == 3 and (lines[j].split()[0][0]!='*' and lines[j].split()[2].isdigit())):
                temp = lines.pop(j)
                lines.insert(initloc, temp)
                initloc+=1
            if(len(lines[j].split())==3 and (lines[j].split()[0][0]!='*' and lines[j].split()[2][0]!='*')):
                arg = lines[j].split()[2]
                
                if(not exists_lhs(lines, arg, initloc, i[1])):
                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1
            if(len(lines[j].split()) == 5):
                arg1 = lines[j].split()[2]
                arg2 = lines[j].split()[4]
                
                if(arg1.isdigit() and arg2.isdigit() and (lines[j].split()[0][0]!='*')):
                    temp = lines.pop(j)
                    lines.insert(initloc, temp)
                    initloc+=1
                elif(arg1.isdigit()and (arg2[0]!='*' and lines[j].split()[0][0]!='*')):
                    if(not exists_lhs(lines, arg2, initloc, i[1])):
                       temp = lines.pop(j)
                       lines.insert(i[0], temp)
                elif(arg2.isdigit()and (arg1[0]!='*' and lines[j].split()[0][0]!='*')):
                    if(not exists_lhs(lines, arg1, initloc, i[1])):
                        temp = lines.pop(j)
                        lines.insert(initloc, temp)
                        initloc+=1
                else:
                    if(not exists_lhs(lines, arg1, initloc, i[1]) and not exists_lhs(lines, arg2, initloc, i[1]) and (arg1[0]!='*' and arg2[0]!='*' and lines[j].split()[0][0]!='*')):
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
                        if x in [">", "<", "=", "!"]:
                            fl = 1
                            continue
                        if (x == "="):
                            continue
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
    print()
    print("___________________________")
    print()
    print("Constant Folding Quadruples")
    print("___________________________")
    print()
    k = 0
    for i in lines:
        
        i = i.strip("\n")
        if k in blocks:
            if(len(i.split()) == 3):
                print("=", rhs, "NULL", lhs)
                time.sleep(0.05)
                lhs, ass, rhs = i.split()
                constantList.append(["=", rhs, "NULL", lhs])
                fullList.append(["=", rhs, "NULL", lhs])
            elif(len(i.split()) == 5):
                print(operator,arg1,arg2,lhs)
                time.sleep(0.05)
                lhs, ass, arg1, operator, arg2 = i.split()
                constantList.append([operator, arg1, arg2, lhs])
            elif(len(i.split()) == 2):
                arg1, arg2 = i.split()
                if(arg1 == "goto"):
                    print("GOTO", arg2)
                    time.sleep(0.05)
                    constantList.append(["GOTO", arg2, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                else:
                    print("LABEL", arg1)
                    time.sleep(0.05)
                    constantList.append(["LABEL", arg1, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
            else:
                if(i.split()[0] == 'ARR'):
                    print(i)
                    constantList.append(i)
                else:
                    cond, arg1, gt, label = i.split();
                    print("IF", arg1, "GOTO", label)
                    time.sleep(0.05)
                    constantList.append(["IF", arg1, "GOTO", label])
                    fullList.append(["IF", arg1, "GOTO", label])
                
        else:
            if(len(i.split()) == 3):
                
                lhs, ass, rhs = i.split()
                if(rhs.isdigit() and (lhs[0]!='*' and rhs[0]!='*')):
                    tempdict[lhs] = rhs;
                    print("=", rhs, "NULL", lhs);
                    time.sleep(0.05)
                    constantList.append(["=", rhs, "NULL", lhs])
                    fullList.append(["=", rhs, "NULL", lhs])
                else:
                    if(rhs in tempdict and (lhs[0]!='*' and rhs[0]!='*')):
                        tempdict[lhs] = tempdict[rhs]
                        print("=", tempdict[rhs], "NULL", lhs)
                        time.sleep(0.05)
                        constantList.append(["=", tempdict[rhs], "NULL", lhs])
                        fullList.append(["=", tempdict[rhs], "NULL", lhs])
                    else:
                        print("=", rhs, "NULL", lhs)
                        time.sleep(0.05)
                        constantList.append(["=", rhs, "NULL", lhs])
                        fullList.append(["=", rhs, "NULL", lhs])
                    
                    
            elif(len(i.split()) == 5):
                lhs, ass, arg1, operator, arg2 = i.split()
                if(operator in ["+", "-", "*", "/"]):
                    if(arg1.isdigit() and arg2.isdigit() and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                        result = eval(arg1+operator+arg2)
                        tempdict[lhs] = result
                        print("=", result, "NULL", lhs)
                        time.sleep(0.05);
                        constantList.append(["=", result, "NULL", lhs])
                        fullList.append(["=", result, "NULL", lhs])
                    elif(arg1.isdigit() and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                        if(arg2 in tempdict):
                            result = eval(arg1+operator+str(tempdict[arg2]))
                            tempdict[lhs] = result
                            print("=", result, "NULL", lhs)
                            time.sleep(0.05)
                            constantList.append(["=", result, "NULL", lhs])
                            fullList.append(["=", result, "NULL", lhs])
                        else:
                            print(operator, arg1, arg2, lhs)
                            time.sleep(0.05)
                            constantList.append([operator, arg1, arg2, lhs])
                            fullList.append([operator, arg1, arg2, lhs])
                    elif(arg2.isdigit() and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                    
                        if(arg1 in tempdict):
                        
                            result = eval(str(tempdict[arg1])+operator+arg2)
                            tempdict[lhs] = result
                            print("=",result,"NULL",lhs)
                            time.sleep(0.05)
                            constantList.append(["=",result,"NULL",lhs])
                            fullList.append(["=",result,"NULL",lhs])
                        else:
                            print(operator,arg1,arg2,lhs)
                            time.sleep(0.05)
                            constantList.append([operator,arg1,arg2,lhs])
                            fullList.append([operator,arg1,arg2,lhs])
                    else:
                        flag1=0
                        flag2=0
                        arg1Res = arg1
                        if(arg1 in tempdict and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                            arg1Res = str(tempdict[arg1])
                            flag1 = 1
                        arg2Res = arg2
                        if(arg2 in tempdict and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                            arg2Res = str(tempdict[arg2])
                            flag2 = 1
                        if(flag1==1 and flag2==1 and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                            result = eval(arg1Res+operator+arg2Res)
                            tempdict[lhs] = result
                            print("=",result,"NULL",lhs)
                            time.sleep(0.05)
                            constantList.append(["=",result,"NULL",lhs])
                            fullList.append(["=",result,"NULL",lhs])
                        else:
                            print(operator,arg1Res,arg2Res,lhs)
                            time.sleep(0.05)
                            constantList.append([operator,arg1Res,arg2Res,lhs])
                            fullList.append([operator,arg1Res,arg2Res,lhs])
            
                elif(operator=="="):
                    if(arg1.isdigit() and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                        tempdict[lhs]=arg1
                        print("=",arg1,"NULL",lhs)
                        time.sleep(0.05)
                        constantList.append(["=",arg1,"NULL",lhs])
                        fullList.append(["=",arg1,"NULL",lhs])
                    else:
                        if(arg1 in tempdict and (lhs[0]!='*' and arg1[0]!='*' and arg2[0]!='*')):
                            print("=",tempdict[arg1],"NULL",lhs)
                            time.sleep(0.05)
                            constantList.append(["=",tempdict[arg1],"NULL",lhs])
                            fullList.append(["=",tempdict[arg1],"NULL",lhs])
                        else:
                            print("=",arg1,"NULL",lhs)
                            time.sleep(0.05)
                            constantList.append(["=",arg1,"NULL",lhs])
                            fullList.append(["=",arg1,"NULL",lhs])
    
                else:
                    print(operator,arg1,arg2,lhs)
                    time.sleep(0.05)
                    constantList.append([operator,arg1,arg2,lhs])
                    fullList.append([operator,arg1,arg2,lhs])
            elif(len(i.split()) == 2):
                arg1, arg2 = i.split()
                if(arg1 == 'goto'):
                    print("GOTO", arg2)
                    time.sleep(0.05)
                    constantList.append(["GOTO", arg2, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                else:
                    print("LABEL", arg1)
                    time.sleep(0.05)
                    constantList.append(["LABEL", arg1, "NULL", "NULL"])
                    fullList.append(["GOTO", arg2, "NULL", "NULL"])
                
            else:
                if(i.split()[0] == 'ARR'):
                    print(i)
                    constantList.append(i)
                else:
                    
                    cond, arg1, gt, label = i.split();
                    print("IF", arg1, "GOTO", label)
                    time.sleep(0.05)
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



def liveVarAnalysis(lines):
    k = 1
    livevariables = []
    varloc = dict()
    for i in lines:
        i = i.strip("\n")
        if(len(i.split()) == 5 or len(i.split()) == 3):
            lhs = i.split()[0]
            out = exists_rhs(lines, lhs, k-1)
            if(out != -1):
                if(lhs not in livevariables):
                    livevariables.append(lhs)
                    varloc[out] = lhs
            if((k-1) in varloc.keys()):
                
                livevariables.remove(varloc[k-1])
            
        print("Live Variables at Line ", k, " Are : ", livevariables)
        time.sleep(0.02)
        k = k + 1
    time.sleep(0.05)
    print("__________________________")
    print()

def checkArray(token, lines, i):
    if('[' in token):
        newptr = "*"
        sub = ""
        trav = 0
        while(token[trav]!='['):
            newptr+=token[trav]
            trav+=1
        trav+=1
        while(token[trav]!=']'):
            sub+=token[trav]
            trav+=1
        print(newptr)
        print(trav)
        return [newptr, sub]
    else:
        return

def additem(newlist, out):
    array = out[0]
    subscript = out[1]
    newstr = array + " = " + array + " + " + subscript
    newlist.append(newstr)
    return newlist

def modifyArray(lines):
    newlist = []
    for i in range(len(lines)):
        lines[i] = lines[i].strip("\n")
        if(len(lines[i].split()) == 3):
            lhs = lines[i].split()[0]
            rhs = lines[i].split()[2]
            out1 = checkArray(lhs, lines, i)
            out2 = checkArray(rhs, lines, i)
            if(out1 != None and out2!=None):
                newlist = additem(newlist, out1)
                newlist = additem(newlist, out2)
                array1 = out1[0]
                array2 = out2[0]
                newline = array1 + " = " + array2
                print(newline)
                newlist.append(newline)
            elif(out1 != None):
                array = out1[0]
                newlist = additem(newlist, out1)
                newline = array + " = " + rhs
                print(newline)
                newlist.append(newline)
            elif(out2 != None):
                array = out2[0]
                newlist = additem(newlist, out2)
                newline = lhs + " = " + array
                print(newline)
                newlist.append(newline)
            elif(out1 == None and out2 == None):
                newlist.append(lines[i])
        elif(len(lines[i].split()) == 5):
            lhs = lines[i].split()[0]
            arg1 = lines[i].split()[2]
            arg2 = lines[i].split()[4]
            out1 = checkArray(lhs, lines, i)
            out2 = checkArray(arg1, lines,i)
            out3 = checkArray(arg2, lines, i)
            if(out1 !=None and out2!=None and out3!=None):
                newlist = additem(newlist, out1)
                newlist = additem(newlist, out2)
                newlist = additem(newlist, out3)
                array1 = out1[0]
                array2 = out2[0]
                array3 = out3[0]
                newline = array1 + " = " + array2 + " " + lines[i].split()[3] + " " + array3
                newlist.append(newline)
            elif(out1 != None and out2 != None):
                newlist = additem(newlist, out1)
                newlist = additem(newlist, out2)
                array1 = out1[0]
                array2 = out2[0]
                newline = array1 + " = " + array2 + " " + lines[i].split()[3] + " " + arg2
                newlist.append(newline)
            elif(out2 != None and out3 != None):
                newlist = additem(newlist, out2)
                newlist = additem(newlist, out3)
                array1 = out2[0]
                array2 = out3[0]
                newline = lhs + " = " + array1 + " " + lines[i].split()[3] + " " + array2
                newlist.append(newline)
            elif(out1 != None and out3 != None):
                newlist = additem(newlist, out1)
                newlist = additem(newlist, out3)
                array1 = out1[0]
                array2 = out3[0]
                newline = array1 + " = " + arg1 + " " + lines[i].split()[3] + " " + array2
                newlist.append(newline)
            elif(out1 != None):
                newlist = additem(newlist, out1)
                array = out1[0]
                newline = array + " = " + arg1 + " " + lines[i].split()[3] + " " + arg2
                newlist.append(newline)
            elif(out2 != None):
                newlist = additem(newlist, out2)
                array = out2[0]
                newline = lhs + " = " + array + " " + lines[i].split()[3] + " " + arg2
                newlist.append(newline)
            elif(out3 != None):
                newlist = additem(newlist, out3)
                array = out3[0]
                newline = lhs + " = " + arg1 + " " + lines[i].split()[3] + " " + array
                print(newline)
                newlist.append(newline)
            else:
                newlist.append(lines[i])
        elif(len(lines[i].split())== 4):
            label = lines[i].split()[3]
            
            if(lines[i].split()[0] == "ARR"):
                newlist.append(lines[i])
                continue
            condition = lines[i].split()[1]
            tempval = 0
            conds = ["=", "!", ">", "<"]
            lhs = ""
            rhs = ""
            condit = ""
            while(tempval<len(condition) and condition[tempval] not in conds):
                lhs+=condition[tempval]
                tempval+=1
            condit+=condition[tempval]
            tempval+=1
            if(tempval <len(condition) and condition[tempval] in conds):
                condit+=condition[tempval]
                tempval+=1
            while(tempval < len(condition)):
                rhs+=condition[tempval]
                tempval+=1
            if('[' in lhs and '[' in rhs):
                out1 = checkArray(lhs, lines, i)
                out2 = checkArray(rhs, lines,i)
                newlist = additem(newlist, out1)
                newlist = additem(newlist, out2)
                newline = "if" + " " + out1[0]+condit+out2[0]+ " " + "goto" + " " + label
                newlist.append(newline)
                print(newline)
            elif('[' in lhs):
                out2 = checkArray(lhs, lines,i)
                newlist = additem(newlist, out2)
                newline = "if" + " " + out2[0]+condit+rhs+ " " + "goto" + " " + label
                newlist.append(newline)
                print(newline)
            elif('[' in rhs):
                out2 = checkArray(rhs, lines,i)
                newlist = additem(newlist, out2)
                newline = "if" + " " + lhs+condit+out2[0]+ " " + "goto" + " " + label
                newlist.append(newline)
                print(newline)
            else:
                newlist.append(lines[i])
            
        else:
            newlist.append(lines[i])
                
    return newlist   
                
    

fin = open("icg.txt", "r")
fout = open("Optim_ICG.txt", "w")
lines = fin.readlines()
print()
print("______________________")
print()
print("Array modification")
lines = modifyArray(lines)


for i in lines:
    print(i)

print()
print("______________________")
print()
print("Live Variable Analysis")
print("______________________")
liveVarAnalysis(lines)
print("Loop Invariant Code Motion")
print("__________________________")
print()
lines, loopblock = loopMotion(lines)
print("_____________________")

print()
print("Dead Code Elimination")
print("_____________________")
print()
lines = elimDeadCode(lines)
printl(lines)
looplines = findLoopLines(lines)
loop = []
for i in range(len(looplines)):
    for j in range(looplines[i][0], looplines[i][1]+1):
        loop.append(j)

constantList, fullList = constantFolding(lines, loop)
print("\n")
print("__________________________")
print()
print("Constant Folded Expression")
print("__________________________")
print()

printExpression(constantList, fout)
fin.close()
fout.close()
#printl(constantList)


