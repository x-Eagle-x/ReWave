#subruledef register
{
    A0 => 0x00
    B0 => 0x01
    C0 => 0x02
    D0 => 0x03
    AX => 0x04
    BX => 0x05
    CX => 0x06
    DX => 0x07
    AY => 0x08
    BY => 0x09
    CY => 0x0A
    DY => 0x0B
    AZ => 0x0C
    BZ => 0x0D
    CZ => 0x0E
    DZ => 0x0F
}

#subruledef operand
{
    {address: u32} => address
    {address: register} => address
}

#subruledef sourcetype
{
    {} => 0x00
    % => 0x80
}

#ruledef
{
    nop => 0x00`8
    ext => 0x01`8
    call {dest: operand} => 0x02`8 @ dest`32
    int {srctype: sourcetype}{src: operand} => (0x03 | srctype)`8 @ src`32
    ret => 0x04`8

    jmp {dest: operand} => 0x05`8 @ dest`32
    jeq {dest: operand} => 0x06`8 @ dest`32
    jnq {dest: operand} => 0x07`8 @ dest`32
    jhi {dest: operand} => 0x08`8 @ dest`32
    jlw {dest: operand} => 0x09`8 @ dest`32
    jhe {dest: operand} => 0x0A`8 @ dest`32
    jle {dest: operand} => 0x0B`8 @ dest`32

    mov {dest: operand}, {srctype: sourcetype}{src: operand} => (0x0C | srctype)`8 @ dest`32 @ src`32
    add {dest: operand}, {srctype: sourcetype}{src: operand} => (0x0D | srctype)`8 @ dest`32 @ src`32
    sub {dest: operand}, {srctype: sourcetype}{src: operand} => (0x0E | srctype)`8 @ dest`32 @ src`32
    div {dest: operand}, {srctype: sourcetype}{src: operand} => (0x0F | srctype)`8 @ dest`32 @ src`32
    mul {dest: operand}, {srctype: sourcetype}{src: operand} => (0x10 | srctype)`8 @ dest`32 @ src`32

    or {dest: operand}, {srctype: sourcetype}{src: operand} => (0x11 | srctype)`8 @ dest`32 @ src`32
    xor {dest: operand}, {srctype: sourcetype}{src: operand} => (0x12 | srctype)`8 @ dest`32 @ src`32
    and {dest: operand}, {srctype: sourcetype}{src: operand} => (0x13 | srctype)`8 @ dest`32 @ src`32
    not {dest: operand}, {srctype: sourcetype}{src: operand} => (0x14 | srctype)`8 @ dest`32 @ src`32
    shl {dest: operand}, {srctype: sourcetype}{src: operand} => (0x15 | srctype)`8 @ dest`32 @ src`32
    shr {dest: operand}, {srctype: sourcetype}{src: operand} => (0x16 | srctype)`8 @ dest`32 @ src`32
    cmp {dest: operand}, {srctype: sourcetype}{src: operand} => (0x17 | srctype)`8 @ dest`32 @ src`32
}
