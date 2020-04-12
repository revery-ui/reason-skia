open BenchFramework;

let options = Reperf.Options.create(~iterations=10000, ());

let noop = () => ();

bench(~name="Noop bench", ~options, ~setup=() => (), ~f=noop, ());
