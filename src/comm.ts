export async function CallServer(request: string): Promise<string> {
  const formData = new FormData();
  return (
    await fetch(`/api_${request}`, {
      method: 'POST',
      body: formData,
    })
  ).text();
}
