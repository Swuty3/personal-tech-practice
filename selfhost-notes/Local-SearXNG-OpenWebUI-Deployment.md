# Local SearXNG & OpenWebUI Deployment

> Personal hands-on deployment notes for a local AI web-search stack. Written for study/self-hosting practice.

In order to provide a search engine for local AI, I deployed SearXNG and OpenWebUI with Docker.

Due to the bad connectivity to the Docker official registry, I added a mirror configuration in “Docker Engine” (Docker Desktop):

```json
{
  "registry-mirrors": [
    "https://dockerproxy.net"
  ]
}
```

The mirror service reference is available at https://dockerproxy.link/

Then it was easier to pull the images:

```bash
docker pull searxng/searxng:latest
docker pull ghcr.io/open-webui/open-webui:main
```

Starting the containers:

```bash
docker run -d \
  --name searxng \
  --network ai-network \
  -p 8081:8080 \
  -v searxng-data:/etc/searxng \
  --restart unless-stopped \
  searxng/searxng:latest
```

```bash
docker run -d \
  --name open-webui \
  --network ai-network \
  -p 3000:8080 \
  -v open-webui-data:/app/backend/data \
  -e OLLAMA_BASE_URL="http://host.docker.internal:11434" \
  -e WEBSEARCH_URL="http://searxng:8080/search?q=<query>" \
  --restart unless-stopped \
  ghcr.io/open-webui/open-webui:main
```

**Command flags explained:**

- `-d`: run in detached (background) mode
- `--name`: assign a human-readable container name for later operations
- `--network ai-network`: attach the container to the custom Docker bridge network `ai-network`
- `-p 8081:8080` / `-p 3000:8080`: port mapping (host port → container internal port)
- `-v`: named volume mount to persist container data
- `-e`: environment variables (here: point Open WebUI to the Ollama service on the Docker host, and to the SearXNG search endpoint)
- `--restart unless-stopped`: auto restart unless the container is manually stopped

After that, I connected SearXNG and Open WebUI through the custom bridge network `ai-network`. Then I opened Open WebUI at `http://localhost:3000` and set “SearXNG's query interface address” to `http://searxng:8080`.

However, I tried many times asking the Ollama model (qwen3:8b) on Open WebUI with the **network search button** enabled. It only seemed to "think" when a link was provided.

By the way, don't ask the AI “Can you search on the Internet?”. The searching actually works through Open WebUI's reply after the AI uses a function tool, so the AI won't admit that it can connect to the Internet.

After a whole day of debugging with no results, I wanted to give up.

At the moment I clicked the Ollama icon and wanted to quit, I found there was a button named “Settings”. I clicked it and saw the “Expose Ollama to the network” option, described as “Allow other devices or services to access Ollama”. That was it! I turned the button on immediately.

However, I thought it was easier to use the Ollama chat itself for searching, since it only needs an account. I was also sure SearXNG could be used from my browser. So I stopped debugging Open WebUI for several days. (2026.9.1)

Today (2026.9.6), I started again.

I asked qwen3:1.7b the weather in my region. It returned fake information because it failed to use `search_web`; it fell back to `fetch_url` and produced AI hallucinations. So I switched to qwen3:8b and tried again, but it still failed.

I guessed the settings might be wrong, so I edited `/etc/searxng/settings.yml`.

I found an incorrect structure in the `search` section:

```yaml
search:
  format:html
  format:json
```

It should be:

```yaml
search:
  formats:
    - html
    - json
```

After fixing that, the AI finally connected to the Internet!

---

Writer: Swuty3
2026.9.6
