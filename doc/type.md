 hex | desc
 ----------
 --- | Integers
  00 | u8
  01 | u16
  02 | u32
  03 | u64
  04 | i8
  05 | i16
  06 | i32
  07 | i64
  0d | utf8 (string)
  0e | Reserved (unsigned bigint)
  0f | Reserved (signed bigint)
 --- | Floating-point
  10 | f32
  11 | f64
  1f | Reserved (decimal)
 --- | Timestamps (future)
  20 | [ u16:YYYY, u8:MM, u8:DD, u8:hh, u8:mm, u8:ss ]
 ---
