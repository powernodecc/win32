### 16位寄存器

+ 通用寄存器

    + AX

      (accumulator)：累加寄存器

    + BX

      base 基址寄存器

    + CX

      count 计数寄存器

    + DX

      data 数据寄存器

+ 段寄存器
    + CS

      code segment 代码段寄存器

    + DS

      data segment 数据段寄存器

    + SS

      stack segment 存放栈顶的段地址

    + ES

      Extra Segment 附加段寄存器

~~~
    程序状态字 
      PSW

    + 标志寄存器
    OF  DF  IF  TF  SF  ZF  AF  PF  CF

    ZF 6bit 零标志位 相关指令执行后结果为0: ZF=1 , 非0: ZF=0
    PF[parity flag] 2bit 奇偶标志位 二进制位1的个数为偶数: PF=1 , 奇数: PF=0
    SF 7bit 符号标志位 指令执行后结果符号位为负: SF=1 , 正: SF=0
    CF 0bit 进位标志位 无符号运算 加法or减法 最高位产生进位(或借位): CF=1 , 否则CF=0
    OF 11bit 溢出标志位 有符号数运算结果发生溢出: OF=1 , 无溢出: OF=0
    AF 辅助进位标志 加法(减法)运算结果的低4位向高4位有进位(或借位)时: AF=1 , 否则AF=0
    TF 跟踪标志位 
    IF 中断标志位
    DF 方向标志位 控制EDI 自增或自减
~~~

    寻址寄存器 | 通用寄存器
      SI（Source Index）：源变址寄存器 
      DI（Destination Index）：目的变址寄存器 

    + IP （Instruction Pointer）：指令指针寄存器

    + SP （Stack Pointer）：堆栈指针寄存器 

    + BP（Base Pointer）：基址指针寄存器 

    EBP 寄存器 栈底指针
    ESP 寄存器 栈顶指针

~~~

    word = 2Byte
    CS:IP
    DS:[address] BP
    SS:SP 指向栈顶元素
    
    mul [计算 8位(AL) 16位(AX)] [结果 8位(AX) 16位 DX(高位) AX(低位)]

    a: above 高于
    b: below 低于
~~~

### 32位寄存器

+ 通用寄存器

~~~
    EAX AX  AH  AL
    EBX BX  BH  BL
    ECX CX  CH  CL
    EDX DX  DH  DL
    32  16  8   8

    call 执行时会 push EIP
    retn 执行时会 pop EIP
    
    [EBP - ??] 本call中的局部变量
    [EBP + ??] 上一个call的局部变量 作为传入参数

    qword ptr quadruple
    
    ! 逻辑取反
    
    条件置位指令: 
    sete(setz) 取ZF标志位的值保存 (==比较时)
    setne(setnz) 取反ZF保存 (!=比较时)
    setg (>比较时) ZF==0 && SF==0 && OF==1 时 al=1
    setl (<) SF==1 || OF==1 时 al=1
    setge (>=)
    setle (<=)

    逻辑运算指令: 
        | or 按位或
        & and 按位与
        ~ not 按位取反
        ^ xor 按位异或
    
    浮点运算
        ST0 - ST7
        80位的两用寄存器
        MMX FPU
        
    浮点指令
        fld  ~= push 
        fstp ~= pop
        fadd ~= add
        fsub ~= sub
        fmul ~= mul
        fdiv ~= div
    
    scasb scasw scasd:
        scas byte ptr [edi] ~= cmp byte ptr [edi],al
        标志位DF为0 inc edi
        标志位DF为1 dec edi
        
    repne:
        指令repnz scasb 编译后: repne scas byte ptr es:[edi]
        ecx!=0 && zf=0 重复执行后边的指令 每执行一次ecx的值减1
    
    repe repz
    repe/repz cmpsb 当ecx!=0并且ZF=1 重复执行后面的指令 每执行一次ecx的值减1
    
    __declspec(naked) 告诉编译器用纯汇编方式编译函数, 不自动添加寄存器保护和堆栈平衡代码

    std DF=1 | cld DF=0 
    
    串存储指令
    stosb stosw stosd ~= mov byte ptr [edi],al   [byte=al,word=ax,dword=eax]
    
    rep stosb  =  rep stos byte ptr [edi] 用al的值填充byte ptr [edi] 每次ecx值减1, edi的值增加1
    
    串载入指令
    lodsb lodsw lodsw lods byte ptr [esi] ~= mov al,byte ptr [esi]
    用byte ptr [esi]的值 填充al 每次ecx值减1 esi的值增加1 |  word ptr [esi] esi+2 |  dword ptr [esi] esi+4

    循环控制指令
    loop 标号 ecx = ecx - 1 , ecx != 0 则转移至标号处循环执行














~~~