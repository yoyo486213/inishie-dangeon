from PIL import Image
import os

# 設定資料夾路徑
folder_path = 'C:/Users/yoyo/Desktop/Project/inishie-dangeon/ptsd-template-main/Resources/temp'

# 取得資料夾內所有的bmp檔案
bmp_files = [f for f in os.listdir(folder_path) if f.endswith('.bmp')]

# 如果資料夾內有bmp檔案
if bmp_files:
    # 讀取第一張圖片
    first_image = Image.open(os.path.join(folder_path, bmp_files[0]))

    # 取得第一張圖片的下半部分 (479x159)
    width, height = first_image.size
    lower_half = first_image.crop((0, height//2, width, height))

    # 替換其他圖片的下半部分
    for bmp_file in bmp_files[1:]:
        image_path = os.path.join(folder_path, bmp_file)
        img = Image.open(image_path)

        # 確保圖片大小為479x354
        if img.size == (479, 354):
            # 分割圖片為上半部和下半部
            upper_half = img.crop((0, 0, width, height//2))

            # 將第一張圖片的下半部粘貼到當前圖片的下半部
            img.paste(lower_half, (0, height//2))

            # 儲存修改後的圖片
            img.save(image_path)

    print("圖片下半部已替換完畢。")
else:
    print("資料夾內沒有bmp檔案。")
