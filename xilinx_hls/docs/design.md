# Swin Transfomer

---
[TOC]

```mermaid
graph LR
    Start  -- H,W,3 --> stage1(Stage Module 1) 
    stage1 -- H/4,W/4,C --> stage2(Stage Module 2)
    stage2 -- H/8,W/8,2C --> stage3(Stage Module 3)
    stage3 -- H/16,W/16,4C --> stage4(Stage Module 4)
    stage4 -- H/32,W/32,8C --> End
```

## Stage Module (Use module 2 as example)

```mermaid
graph LR
    Start -- H/4,W/4,C --> pp(Partition Patch)
    pp -- H/8,W/8,2C --> sb1(Swin Block)
    sb1 -- H/8,W/8,2C --> sb2("Swin Block(Shift Window)")
    sb2 -- H/8,W/8,2C --> End
```

### Partition Merge

```mermaid
graph LR
    Start -- H/4,W/4,C --> ur(Unfolder Resharp)
    ur -- H/8,W/8,4C --> lr(Linear)
    lr -- H/8,W/8,2C --> End
```

#### Unfolder Resharp

实际上Unfold的作用如下图所示

@import "http://cdn.dianhsu.top/img/20210524135033.svg" {width=450}

输入数据是一个 $H,W,C$ 的立方体，Unfolder Resharp的作用是将它切分成 $ds, ds, C$ 的小立方体立方体。那么立方体的个数是$\frac{W \times H}{ds^2}$，将小立方体的数据排成一排。得到的输出就是$[\frac{W \times H}{ds^2}, ds^2 \times C ]$。


#### Linear


### Swin Block


### Swin Block(Shift Window)