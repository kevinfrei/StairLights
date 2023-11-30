import { promises as fsp } from 'fs';
import path from 'path';
import { ForFiles } from "@freik/node-utils";

// What to do here, I wonder...

type MimeFile = { mime: string; name: string };
type PathBufInfo = MimeFile & { varname: string, namelen: number };
type FullBufInfo = PathBufInfo & { contentlen: number };

async function getFileList(): Promise<MimeFile[]> {
  const res: MimeFile[] = [];
  await ForFiles("build", (filename: string): boolean => {
    const name = filename.substring(6);
    const mime = path.extname(filename).substring(1).toLowerCase();
    res.push({ mime, name });
    return true;
  }, { keepGoing: true });
  return res;
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
    const varname = CleanPath(f.name, names);
    console.log(`  constexpr char ${varname}[] = "${f.name}";`);
    res.push({ ...f, varname, namelen: f.name.length });
  });
  console.log('} // namespace Paths\n\n');
  return res;
}

async function generateContents(files: PathBufInfo[]): Promise<FullBufInfo[]> {
  const res: FullBufInfo[] = [];
  console.log("namespace Contents {");
  files.forEach((f: PathBufInfo) => {
      console.log(`  constexpr char ${f.varname}[] = "TODO: Fill in with contents of ${f.name}";`);
      res.push({ ...f, contentlen: 123 })
    }
  );
  console.log("} // namespace Contents\n\n");
  return res;
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
  console.log(`constexpr WebFile FileList[${contentInfo.length}] = {`);
  contentInfo.forEach((i: FullBufInfo) => {
    console.log(`  { Mime::${i.mime},`);
    console.log(`    { ${i.varname.length}, Paths::${i.varname} },`);
    console.log(`    { ${i.contentlen}, Contents::${i.varname} }`);
    console.log(`  },`);
  });
  console.log('};');
}

main().catch(console.error);
