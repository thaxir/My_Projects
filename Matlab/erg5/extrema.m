function points = extrema( ekfrash )

df = diff(sym(ekfrash));
points = solve(df);

end

