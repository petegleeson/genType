module type MT = {
  let x: int;
  type t = int;
  [@bs.module "foo"] external f: int => int = "";
  module type XXX = {type tt = string;};
  module EmptyInnerModule: {};
  module InnerModule2: {let k: t;};
  module InnerModule3: {
    type inner = int;
    let k3: inner => inner;
  };
  module type TT = {let u: (int, int);};
  module Z: TT;
  let y: string;
};
module M = {
  let y = "abc";
  module type XXX = {type tt = string;};
  module EmptyInnerModule = {};
  module InnerModule2 = {
    let k = 4242;
  };
  module InnerModule3 = {
    type inner = int;
    let k3 = x => x + 1;
  };

  module type TT = {let u: (int, int);};
  module Z = {
    let u = (0, 0);
  };
  type t = int;
  [@bs.module "foo"] external f: int => int = "";
  let x = 42;
};

[@genType]
type firstClassModule = (module MT);

[@genType]
let firstClassModule: firstClassModule = (module M);

[@genType]
let testConvert = (m: (module MT)) => m;

module type ResT = {let ww: string;};

module SomeFunctor = (X: MT) : ResT => {
  let ww = X.y;
};

[@genType]
let someFunctorAsFunction = (x: (module MT)): (module ResT) =>
  (module SomeFunctor((val x)));