# github 常用指令
A Big Cookie  
A Piece Of Cake  

- 基礎  
  git add .  # 新增檔案到暫存  
  git commit -m "message"  # 新增變更  
  git push # 推送至雲端  
  git status # 查看狀態  
  git stash # 暫存所有未提交的變更  
  git stash pop # 取回變更  

- Branck分支  
  git checkout -b branch # 建立並切換到分支  
  git branch -d branch # 刪除分支  
  git push (-u) origin branch # 推送至分支 (-u 新增並上傳本地branch至github)  
  git pull origin branch # 從分支拉取  

- Log
  git reflog # 找回最近的Git操作記錄  
  git reset --hard (number) # 回復到指定狀態

  好的，這裡是使用 git pull 的說明、用法、指令及其在不同情況下的行為整理：

- git pull 進階  
  git pull 是 Git 中用來從遠端儲存庫拉取（fetch）最新的更改並將其與本地的分支合併（merge）的指令。它相當於執行 git fetch 和 git merge 兩個操作。  

  git pull 做了什麼
  當執行 git pull 時，Git 會進行以下兩個步驟：

  (1) 從遠端拉取最新更新（fetch）
  Git 會從遠端儲存庫拉取所有最新的提交，包括新增的文件、修改過的文件、刪除的文件等，並更新本地的遠端追蹤分支。

  (2) 合併遠端更改（merge）
  Git 會自動將遠端儲存庫的更改合併到本地分支。如果有衝突，Git 會提示你解決衝突。

  git pull origin main # 這樣會從遠端儲存庫 origin 拉取 main 分支的更新並合併到本地的 main 分支。

  4. git pull 可能遇到的情況及如何處理
  (1) 本地有修改，遠端有修改
  合併（merge）：Git 會嘗試將本地的更改與遠端的更改合併。
  衝突（conflict）：如果本地和遠端對同一部分代碼有不同修改，Git 會標註為衝突，並要求你手動解決衝突。

  (2) 本地刪除文件，遠端新增文件
  如果本地刪除了某個文件，且遠端新增了相同文件，Git 會提示衝突。你可以選擇保留本地的刪除，或者恢復遠端的新增。
  
  保留本地刪除：
  git rm <file-name>  # 刪除本地文件
  git commit          # 提交更改
  
  保留遠端新增：
  git checkout -- <file-name>  # 恢復遠端版本的文件
  git add <file-name>          # 添加文件
  git commit                   # 提交
  
  (3) 本地新增文件，遠端刪除文件
  如果本地新增了某個文件，且遠端刪除了該文件，Git 會提示衝突。你可以選擇保留本地新增，或刪除本地文件來與遠端保持一致。

  保留本地新增：
  git add <file-name>   # 添加文件
  git commit            # 提交
  
  保留遠端刪除：
  git rm <file-name>  # 刪除本地文件
  git commit          # 提交
  (4) 文件名衝突（重命名）
  如果本地和遠端對同一文件進行了重命名，Git 會視為衝突，需要手動解決。
  
  保留遠端重命名：
  git mv <old-file-name> <new-file-name>  # 重命名文件
  git add <new-file-name>                 # 添加更改
  git commit                              # 提交
  
  保留本地重命名：
  git mv <old-file-name> <new-file-name>  # 重命名文件
  git add <new-file-name>                 # 添加更改
  git commit                              # 提交
  
  (5) 文件在遠端刪除，本地修改過該文件
  如果文件在遠端被刪除，而你本地對該文件有修改，Git 會提示衝突。你可以選擇保留本地修改，或者刪除本地文件來與遠端一致。

  保留本地修改：
  git add <file-name>   # 添加文件
  git commit            # 提交
  
  保留遠端刪除：
  git rm <file-name>  # 刪除本地文件
  git commit          # 提交
  
  5. 其他常見 git pull 選項
  git pull --rebase： 使用 --rebase 選項可以避免產生合併提交，並且將本地提交"重演"在遠端提交之後，讓提交歷史更加乾淨。
  
  git pull --rebase origin main
  這樣會將你的本地修改“放置”在遠端的更改之後。
  
  git pull --no-commit： 防止 Git 在合併後自動提交，這樣你可以先檢查更改，確保一切正確後再提交。

  git pull --no-commit origin main
