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

#subruledef destinationtype
{
    {} => 0
    % => 0b10000000
}

#subruledef sourcetype
{
    {} => 0
    % => 0b01000000
}

#ruledef
{
    nop => 0x00`8
    ext => 0x01`8
    call {desttype: destinationtype}{dest: operand} => (0x02 | desttype)`8 @ dest`32
    int {desttype: destinationtype}{dest: operand} => (0x03 | desttype)`8 @ dest`32
    ret => 0x04`8

    jmp {desttype: destinationtype}{dest: operand} => 0x05`8 @ dest`32
    jeq {desttype: destinationtype}{dest: operand} => 0x06`8 @ dest`32
    jnq {desttype: destinationtype}{dest: operand} => 0x07`8 @ dest`32
    jhi {desttype: destinationtype}{dest: operand} => 0x08`8 @ dest`32
    jlw {desttype: destinationtype}{dest: operand} => 0x09`8 @ dest`32
    jhe {desttype: destinationtype}{dest: operand} => 0x0A`8 @ dest`32
    jle {desttype: destinationtype}{dest: operand} => 0x0B`8 @ dest`32

    mov {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x0C | desttype | srctype)`8 @ dest`32 @ src`32
    add {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x0D | desttype | srctype)`8 @ dest`32 @ src`32
    sub {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x0E | desttype | srctype)`8 @ dest`32 @ src`32
    div {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x0F | desttype | srctype)`8 @ dest`32 @ src`32
    mul {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x10 | desttype | srctype)`8 @ dest`32 @ src`32

    or {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x11 | desttype | srctype)`8 @ dest`32 @ src`32
    xor {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x12 | desttype | srctype)`8 @ dest`32 @ src`32
    and {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x13 | desttype | srctype)`8 @ dest`32 @ src`32
    not {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x14 | desttype | srctype)`8 @ dest`32 @ src`32
    shl {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x15 | desttype | srctype)`8 @ dest`32 @ src`32
    shr {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x16 | desttype | srctype)`8 @ dest`32 @ src`32
    cmp {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x17 | desttype | srctype)`8 @ dest`32 @ src`32
    load {desttype: destinationtype}{dest: operand}, {srctype: sourcetype}{src: operand} => (0x18 | desttype | srctype)`8 @ dest`32 @ src`32
}
