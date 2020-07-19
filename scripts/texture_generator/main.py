import sys
from pathlib import Path

import click
from PIL import Image

def process_psd(file_path: Path, out_path: Path) -> None:
	png_path = out_path.joinpath("/".join(file_path.parts[1:])).with_suffix(".png")
	with Image.open(file_path) as image:
		image.save(png_path)

@click.command()
@click.option('--in_dir', prompt='Input path', help='The path to directory containing psd files')
@click.option('--out_dir', prompt='Output path', help='The path to place output')
def main(in_dir: str, out_dir: str) -> None:
	input_dir = Path(in_dir)
	output_dir = Path(out_dir)

	if not input_dir.exists():
		print("ERROR: No such directory:", input_dir)
		sys.exit(1)

	if not output_dir.exists():
		output_dir.mkdir()

	files_processed = 0
	for sub in input_dir.iterdir():
		output_dir.joinpath("/".join(sub.parts[1:])).mkdir()

	for psd_file in input_dir.glob("**/*.psd"):
		process_psd(psd_file, output_dir)
		files_processed += 1

	if files_processed == 0:
		print("ERROR: No psd files found under: ", input_dir)
		sys.exit(1)

if __name__ == '__main__':
	main() # pylint: disable=no-value-for-parameter
