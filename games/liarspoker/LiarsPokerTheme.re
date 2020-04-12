module Colors = {
  open Css;

  let table = rgba(0, 100, 0, 1.0);
};

module Table = {
  let tableGradient =
    Css.(
      radialGradient([
        (pct(62.0), Colors.table),
        (pct(62.5), rgba(192, 192, 0, 0.9)),
        (pct(63.0), Colors.table),
        (pct(65.0), Colors.table),
        (pct(66.0), rgba(20, 20, 20, 1.0)),
        (pct(70.0), rgba(35, 35, 35, 1.0)),
      ])
    );

  let tableStyle =
    Css.(
      style([
        position(absolute),
        height(pct(100.0)),
        width(pct(100.0)),
        gridRowStart(1),
        gridColumnStart(1),
        display(inlineBlock),
        backgroundImage(
          radialGradient([
            (pct(62.0), rgba(0, 100, 0, 1.0)),
            (pct(62.5), rgba(192, 192, 0, 0.9)),
            (pct(63.0), rgba(0, 100, 0, 1.0)),
            (pct(65.0), rgba(0, 100, 0, 0.8)),
            (pct(66.0), rgba(20, 20, 20, 1.0)),
            (pct(70.0), rgba(35, 35, 35, 1.0)),
          ]),
        ),
        unsafe("clipPath", "circle(closest-side)"),
      ])
    );

  let elementContainerStyle = (i, angleStep) =>
    Css.(
      style([
        display(`flex),
        flexDirection(row),
        width(pct(100.0)),
        height(pct(100.0)),
        position(relative),
        transforms([
          translateY(pct((-100.0) *. float_of_int(i))),
          rotate(turn(angleStep *. float_of_int(i) +. 0.25)),
          translateY(pct(50.0)),
        ]),
        before([contentRule(`text(""))]),
      ])
    );

  let elementWrapperStyle =
    Css.(
      style([
        display(inlineBlock),
        top(pct(50.0)),
        unsafe("height", "min-content"),
        color(white),
        transforms([translateY(pct(-50.0)), rotate(turn(-0.25))]),
      ])
    );

  let centerContainerStyle =
    Css.(
      style([
        position(absolute),
        gridRowStart(1),
        gridColumnStart(1),
        display(inlineBlock),
      ])
    );
};
