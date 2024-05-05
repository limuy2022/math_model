def prepare(path, form: str, year):
    year += 10
    with open(path, "r") as f:
        for i in range(21):
            f.readline()
        with open(f"tmp{form.lower()}.csv", "w") as ff:
            cnt = 1
            tmp = 0
            ff.write(f"DATE,{form.upper()}\n")
            flag = False
            for i in f:
                l = [i.strip() for i in i.split(",")]
                if l[2][:4] != "1877" and not flag:
                    continue
                flag = True
                tmp += int(l[3])
                cnt += 1
                if cnt % 30 == 0:
                    ff.write(f"{int(cnt/30)},{tmp/30}\n")
                    tmp = 0
                if cnt > 365 * year:
                    break
