Random.self_init();

let gen_code = (len: int) => {
  let gen = () =>
    switch (Random.int(26 + 10)) {
    | n when n < 26 => int_of_char('a') + n
    | n => int_of_char('0') + n - 26
    };
  let gen = () => String.make(1, char_of_int(gen()));
  Belt.Array.(makeBy(len, _ => gen())->(reduce("", (++))));
};

module Matrix = {
  type matrix('a) = array(array('a));

  let flat_reduce = (m: matrix('a), acc: 'b, f: ('b, 'a) => 'b) =>
    Belt.Array.(m->reduce(acc, (acc, row) => row->reduce(acc, f)));
};

module OnLoad = {
  [@react.component]
  let make = (~children) => {
    React.useEffect0(() => {
      children();
      None;
    });
    React.null;
  };
};
