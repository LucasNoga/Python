def main():
    a = (
        ("Sword Art Online", "Shingeki no Kyojin", "Danmachi"),
        ("Akame ga Kill", "Parasite", "No Game No Life", "Tokyo Ghoul"),
        ("Code Geass", "Nanatsu no Taizai", "Ajin", "High School DxD", "Mirai Nikki")
    )

    a = sorted(a, key=lambda x: x[len(x) - 1], reverse=False)
    print(type(a))
    print("[")

    for x in a:
        print("\t" + str(x))

    print("]")


if __name__ == "__main__":
    main()
