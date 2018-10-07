open Belt;

[@genType]
type coord = {
  x: int,
  y: int,
  z: option(int),
};

[@genType]
let origin = {x: 0, y: 0, z: Some(0)};

[@genType]
let computeArea = ({x, y, z}) =>
  Option.(x * y * z->(mapWithDefault(1, n => n)));

[@genType]
let coord2d = (x, y) => {x, y, z: None};

[@genType]
type person = {
  name: string,
  age: int,
  address: option(string),
};

[@genType]
type business = {
  name: string,
  owner: option(person),
  address: option(string),
};

let getOpt = (opt, default, foo) => opt->Option.mapWithDefault(default, foo);

[@genType]
let findAddress = (business: business): list(string) =>
  business.address->getOpt([], a => [a]);

[@genType]
let someBusiness = {name: "SomeBusiness", owner: None, address: None};

[@genType]
let findAllAddresses = (businesses: array(business)): array(string) =>
  businesses
  ->Array.map(business =>
      business.address->getOpt([], a => [a])
      @ business.owner->getOpt([], p => p.address->getOpt([], a => [a]))
    )
  ->List.fromArray
  ->List.flatten
  ->List.toArray;

[@genType]
type payload('a) = {
  num: int,
  payload: 'a,
};

[@genType]
let getPayload = ({payload}) => payload;

[@genType]
type record = {
  v: int,
  w: int,
};

[@genType]
let getPayloadRecord = ({payload}): record => payload;

[@genType]
let recordValue = {v: 1, w: 1};

[@genType]
let payloadValue = {num: 1, payload: recordValue};

[@genType]
let getPayloadRecordPlusOne = ({payload}): record => {
  ...payload,
  v: payload.v + 1,
};

[@genType]
type business2 = {
  name: string,
  owner: Js.Nullable.t(person),
  address2: Js.Nullable.t(string),
};

[@genType]
let findAddress2 = (business: business2): list(string) =>
  business.address2->Js.Nullable.toOption->getOpt([], a => [a]);

[@genType]
let someBusiness2 = {
  name: "SomeBusiness",
  owner: Js.Nullable.null,
  address2: Js.Nullable.null,
};

[@genType]
let computeArea3 =
    (
      o: {
        .
        "x": int,
        "y": int,
        "z": Js.Nullable.t(int),
      },
    ) =>
  o##x * o##y * o##z->Js.Nullable.toOption->Option.mapWithDefault(1, n => n);

[@genType]
let computeArea4 =
    (
      o: {
        .
        "x": int,
        "y": int,
        "z": option(int),
      },
    ) =>
  o##x * o##y * o##z->Option.mapWithDefault(1, n => n);