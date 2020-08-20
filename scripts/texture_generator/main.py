import sys
import shutil
from pathlib import Path

import click
from psd_tools import PSDImage

def process_psd(file_path: Path, out_path: Path) -> None:
	png_path = out_path.joinpath("/".join(file_path.parts[1:])).with_suffix(".png")
	psd = PSDImage.open(file_path)
	psd.composite().save(png_path)

@click.command()
@click.option('--in', prompt='Input path', help='The path to directory containing psd files')
@click.option('--out', prompt='Output path', help='The path to place output')
def main(**kwargs: str) -> None:
	input_dir = Path(kwargs["in"])
	output_dir = Path(kwargs["out"])

	print(f"Generating art assets: {str(input_dir)} -> {str(output_dir)}")
	if not input_dir.exists():
		print("ERROR: No such directory:", input_dir)
		sys.exit(1)

	if output_dir.exists():
		shutil.rmtree(output_dir)
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
