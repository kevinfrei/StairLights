import fs, { promises as fsp } from 'fs';
import path from 'path';
import util from 'util';
import { ForFiles } from '@freik/node-utils';

var log_file = fs.createWriteStream('controller/webcontent.h', { flags: 'w' });
// var log_stdout = process.stdout;

// Tee between console and a file by commenting out the second line
console.log = function (d) {
  log_file.write(util.format(d) + '\n');
  // log_stdout.write(util.format(d) + '\n');
};

// What to do here, I wonder...

type MimeFile = { mime: string; name: string };
type PathBufInfo = MimeFile & { varname: string; namelen: number };
type FullBufInfo = PathBufInfo & { contentlen: number };

async function getFileList(): Promise<MimeFile[]> {
  const res: MimeFile[] = [];
  await ForFiles(
    'build',
    (filename: string): boolean => {
      // Don't include any map or txt files. They're just filler.
      if (!filename.endsWith('.map') && !filename.endsWith('.txt')) {
        const name = filename.substring(6);
        const mime = path.extname(filename).substring(1).toLowerCase();
        res.push({ mime, name });
      }
      return true;
    },
    { keepGoing: true },
  );
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
  console.log('  const char _root_[] = "";');
  console.log('  const char _index_htm_[] = "index.htm";');
  names.add('_root_');
  names.add('_index_htm_');
  for (const f of files) {
    const varname = CleanPath(f.name, names);
    console.log(`  const char ${varname}[] = "${f.name}";`);
    res.push({ ...f, varname, namelen: f.name.length });
  }
  console.log('} // namespace Paths\n\n');
  return res;
}

async function writeBinaryFileContents(f: string): Promise<number> {
  const fd = await fsp.open('build/' + f, 'r');
  const stat = await fd.stat();
  try {
    let remain = stat.size;
    let line = '    ';
    while (remain > 0) {
      const res = await fd.read();
      remain -= res.bytesRead;
      // Write the bytes, in hex, to the console
      for (let i = 0; i < res.bytesRead; i++) {
        const expr = `${res.buffer[i].toString(10)},`;
        if (line.length + expr.length > 80) {
          console.log(line);
          line = '    ';
        }
        line += expr;
      }
    }
    console.log(line);
    console.log('  };');
    return stat.size;
  } finally {
    await fd.close();
  }
}

async function generateContents(files: PathBufInfo[]): Promise<FullBufInfo[]> {
  const res: FullBufInfo[] = [];
  console.log('namespace Contents {');
  for (const f of files) {
    console.log(`  const char ${f.varname}[] = {`);
    // TODO: Handle text files more optimally...
    // TODO: Also maybe compress/decompress stuff
    const contentlen = await writeBinaryFileContents(f.name);
    res.push({ ...f, contentlen });
  }
  console.log('} // namespace Contents\n\n');
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
  const index = contentInfo.find(
    (val: FullBufInfo) => val.name === 'index.html',
  );
  console.log(
    `const WebFile FileList[${
      contentInfo.length + (index !== undefined ? 2 : 0)
    }] = {`,
  );
  if (index !== undefined) {
    console.log(`  { Mime::html,`);
    console.log(`    { 0, Paths::_root_ },`);
    console.log(`    { ${index.contentlen}, Contents::index_html }`);
    console.log(`  },`);
    console.log(`  { Mime::html,`);
    console.log(`    { 9, Paths::_index_htm_ },`);
    console.log(`    { ${index.contentlen}, Contents::index_html }`);
    console.log(`  },`);
  }
  contentInfo.forEach((i: FullBufInfo) => {
    console.log(`  { Mime::${i.mime},`);
    console.log(`    { ${i.varname.length}, Paths::${i.varname} },`);
    console.log(`    { ${i.contentlen}, Contents::${i.varname} }`);
    console.log(`  },`);
  });
  console.log('};');
}

main().catch(console.error);
