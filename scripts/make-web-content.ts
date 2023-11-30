import { promises as fsp } from 'fs';

// What to do here, I wonder...

type MimeFile = { mime: string; name: string };
type PathBufInfo = MimeFile & { pathinfo: string };
type FullBufInfo = PathBufInfo & { contentinfo: { len: number; name: string } };

async function getFileList(): Promise<MimeFile[]> {
  return [];
}

function CleanPath(p: string, names: Set<string>): string {
  let res = p.replace(/[^a-zA-Z0-9]/g, '_').toLowerCase();
  if (names.has(res)) {
    let number = 2;
    while (names.has(`${res}${number}`)) {
      number++;
    }
    res = `${res}${number}`;
  }
  names.add(res);
  return res;
}

function generatePathsList(files: MimeFile[]): PathBufInfo[] {
  const res: PathBufInfo[] = [];
  const names = new Set<string>();
  console.log('namespace Paths {');
  files.forEach((f: MimeFile) => {
    const pathinfo = CleanPath(f.name, names);
    console.log(`  constexpr char ${pathinfo}[] = "${f.name}";`);
    res.push({ ...f, pathinfo });
  });
  console.log('}');
  return res;
}

async function generateContents(files: PathBufInfo[]): Promise<FullBufInfo[]> {
  return [];
}

async function main() {
  // Read all the static files from the 'build' directory
  // generate a header named "webcontent.h"
  // First get the file list
  const files: MimeFile[] = await getFileList();
  // From the file list, spit out the file names into the "Paths" namespace:
  const filePaths: PathBufInfo[] = await generatePathsList(files);
  // Again, from the file list, put the content of the files into the "Contents" namespace:
  const contentInfo: FullBufInfo[] = await generateContents(filePaths);
  // Finally, generate the WebMap linear lookup table
  // It's a linear lookup because I just don't expect very much content, and a linear search
  // of the paths is fine for now.
  console.log(`constexpr WebMap FileList[${contentInfo.length}] {`);
  contentInfo.forEach((i: FullBufInfo) => {
    console.log(`  {Mime::${i.mime},`);
    console.log(`    {${i.pathinfo.length}, Paths::${i.pathinfo}},`);
    console.log(`    {${i.contentinfo.len}, Contents::${i.contentinfo.name}}`);
    console.log(`  },`);
  });
  console.log('};');
}

main().catch(console.error);
