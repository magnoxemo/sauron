cd build/test
for file in test*; do
    if [[ -x "$file" && ! -d "$file" ]]; then
        echo "Running $file-------"
        ./$file
    fi
done