function deriv = der( ekfrash , n)

deriv(1) = diff(sym(ekfrash))
for i = 2:n
    deriv(i) = diff(sym(deriv(i-1)))
end

end

