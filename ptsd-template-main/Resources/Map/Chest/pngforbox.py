from PIL import Image
import os

def slice_image(image_path, output_folder, slice_width, slice_height):
    # 確保輸出資料夾存在
    os.makedirs(output_folder, exist_ok=True)

    # 加載圖片
    img = Image.open(image_path)
    img_width, img_height = img.size

    # 圖片尺寸檢查
    if img_width < slice_width or img_height < slice_height:
        print(f"圖片尺寸為 {img_width}x{img_height}，請確認圖片是否符合要求！")
        return

    print(f"開始切割圖片，尺寸：{img_width}x{img_height}，生成由左往右的切片")

    # 由左往右逐漸切片，每次增加 `slice_width` 的寬度
    for i in range(1, img_width + 1):
        # 計算目前切割區域的高度，從下往上長
        left = img_width - i  # 開始的高度
        right = left + slice_width  # 截止的高度

        # 如果這個切片區域超出了圖片的範圍，則跳過
        if left < 0:
            break
        
        # 裁剪區域：(left, upper, right, lower)
        slice_img = img.crop((left, 0, right, slice_height))

        # 確保每個切片的大小為 27x30，並填充透明背景
        transparent_img = Image.new("RGBA", (slice_width, slice_height), (0, 0, 0, 0))
        
        # 使圖片對齊底部，將裁剪後的圖片粘貼在透明背景的底部
        transparent_img.paste(slice_img, (slice_width - i, 0))

        # 保存切片，文件名按順序編號
        output_path = os.path.join(output_folder, f"XPBar-{i:02d}.png")
        transparent_img.save(output_path)

        print(f"已保存切片: {output_path}")

    print("✅ 圖片由下往上遞增切片完成！")

# 使用函式
slice_image(
    "C:/Users/USER/Desktop/for_git/OOPLab_113-2/inishie-dangeon/ptsd-template-main/Resources/UI/Origin/XPBar.png",
    "C:/Users/USER/Desktop/for_git/OOPLab_113-2/inishie-dangeon/ptsd-template-main/Resources/UI/Origin/XPBar",
    75, 10  # 每個切片的大小 (寬50px，高5px)
)
